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
* @file xe_cmdlist.hpp
*
* @brief C++ wrapper of Intel Xe Driver APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDLIST_HPP
#define _XE_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList
    {
    protected:
        ::xe_command_list_handle_t handle;                ///< handle of command list object
        ::xe_command_list_desc_t desc;                    ///< descriptor of the command list object

    public:
        auto getHandle( void ) const { return handle; }
        auto getDesc( void ) const { return desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_host_pfn_t
        using host_pfn_t = ::xe_host_pfn_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_list_parameter_t
        enum class command_list_parameter_t
        {
            TBD,                                            ///< TBD

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_format_t
        enum class command_format_t
        {
            NATIVE,                                         ///< The commands are native device-specific format

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_memory_advice_t
        enum class memory_advice_t
        {
            SET_READ_MOSTLY = 0,                            ///< hint that memory will be read from frequently and written to rarely
            CLEAR_READ_MOSTLY,                              ///< removes the affect of ::MEMORY_ADVICE_SET_READ_MOSTLY
            SET_PREFERRED_LOCATION,                         ///< hint that the preferred memory location is the specified device
            CLEAR_PREFERRED_LOCATION,                       ///< removes the affect of ::MEMORY_ADVICE_SET_PREFERRED_LOCATION
            SET_ACCESSED_BY,                                ///< hint that memory will be accessed by the specified device
            CLEAR_ACCESSED_BY,                              ///< removes the affect of ::MEMORY_ADVICE_SET_ACCESSED_BY
            SET_NON_ATOMIC_MOSTLY,                          ///< hints that memory will mostly be accessed non-atomically
            CLEAR_NON_ATOMIC_MOSTLY,                        ///< removes the affect of ::MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
            BIAS_CACHED,                                    ///< hints that memory should be cached
            BIAS_UNCACHED,                                  ///< hints that memory should be not be cached

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_region_t
        struct image_region_t
        {
            size_t offset = 0;                              ///< [in] offset in bytes from base
            size_t size = 0;                                ///< [in] size in bytes from base+offset

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_dispatch_function_arguments_t
        struct dispatch_function_arguments_t
        {
            uint32_t groupCountX = 0;                       ///< [in] width of dispatches in X dimension
            uint32_t groupCountY = 0;                       ///< [in] width of dispatches in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] width of dispatches in Z dimension

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeExecutionBarrier
        inline void EncodeExecutionBarrier(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListDestroy
        inline void Destroy(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListClose
        inline void Close(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListReset
        inline void Reset(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListSetParameter
        inline void SetParameter(
            command_list_parameter_t parameter,             ///< [in] parameter to change
            uint32_t value                                  ///< [in] value of attribute
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListGetParameter
        inline void GetParameter(
            command_list_parameter_t parameter,             ///< [in] parameter to retrieve
            uint32_t* value                                 ///< [out] value of attribute
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListResetParameters
        inline void ResetParameters(
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeCommandLists
        inline void EncodeCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to encode
            command_list_handle_t* phCommandLists           ///< [in] list of handles of the command lists to encode for execution
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeCommands
        inline void EncodeCommands(
            command_format_t format,                        ///< [in] format of the command blob
            size_t size,                                    ///< [in] size (in bytes) of the command blob
            void* pBlob                                     ///< [in] pointer to blob of commands to encode into the command list
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListReserveSpace
        inline void ReserveSpace(
            size_t size,                                    ///< [in] size (in bytes) to reserve
            void** ptr                                      ///< [out] pointer to command buffer space reserved
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeMemoryCopy
        inline void EncodeMemoryCopy(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size                                     ///< [in] size in bytes to copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeMemorySet
        inline void EncodeMemorySet(
            void* ptr,                                      ///< [in] pointer to memory to initialize
            int value,                                      ///< [in] value to initialize memory to
            size_t size                                     ///< [in] size in bytes to initailize
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeImageCopy
        inline void EncodeImageCopy(
            image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
            image_handle_t hSrcImage                        ///< [in] handle of source image to copy from
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyRegion
        inline void EncodeImageCopyRegion(
            image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
            image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
            image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
            image_region_t* pSrcRegion                      ///< [in][optional] source region descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyToMemory
        inline void EncodeImageCopyToMemory(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
            image_region_t* pSrcRegion                      ///< [in][optional] source region descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyFromMemory
        inline void EncodeImageCopyFromMemory(
            image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
            image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
            const void* srcptr                              ///< [in] pointer to source memory to copy from
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeMemoryPrefetch
        inline void EncodeMemoryPrefetch(
            const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
            size_t count                                    ///< [in] size in bytes of the memory region to prefetch
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeMemAdvise
        inline void EncodeMemAdvise(
            device_handle_t hDevice,                        ///< [in] device associated with the memory advice
            const void* ptr,                                ///< [in] Pointer to the start of the memory range
            size_t size,                                    ///< [in] Size in bytes of the memory range
            memory_advice_t advice                          ///< [in] Memory advice for the memory range
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeSignalEvent
        inline void EncodeSignalEvent(
            event_handle_t hEvent                           ///< [in] handle of the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeWaitOnEvent
        inline void EncodeWaitOnEvent(
            event_handle_t hEvent                           ///< [in] handle of the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeEventReset
        inline void EncodeEventReset(
            event_handle_t hEvent                           ///< [in] handle of the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeDispatchFunction
        inline void EncodeDispatchFunction(
            function_handle_t hFunction,                    ///< [in] handle of the function object
            const dispatch_function_arguments_t* pDispatchFuncArgs, ///< [in] dispatch function arguments.
            event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeDispatchFunctionIndirect
        inline void EncodeDispatchFunctionIndirect(
            function_handle_t hFunction,                    ///< [in] handle of the function object
            const dispatch_function_arguments_t* pDispatchArgumentsBuffer,  ///< [in] pointer to device buffer that will contain dispatch arguments
            event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeDispatchMultipleFunctionsIndirect
        inline void EncodeDispatchMultipleFunctionsIndirect(
            uint32_t numFunctions,                          ///< [in] maximum number of functions to dispatch
            const function_handle_t* phFunctions,           ///< [in] handles of the function objects
            const size_t* pNumDispatchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                            ///< number of dispatch arguments; must be less-than or equal-to
                                                            ///< numFunctions
            const dispatch_function_arguments_t* pDispatchArgumentsBuffer,  ///< [in] pointer to device buffer that will contain a contiguous array of
                                                            ///< dispatch arguments
            event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListEncodeDispatchHostFunction
        inline void EncodeDispatchHostFunction(
            host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
            void* pUserData                                 ///< [in] pointer to user data to pass to host function.
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDLIST_HPP
