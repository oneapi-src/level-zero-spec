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
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command List
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
        /// @brief C++ version for ::xe_command_list_desc_version_t
        enum class command_list_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_list_flag_t
        enum class command_list_flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = XE_BIT(0),                          ///< command list **only** contains copy operations (and synchronization
                                                            ///< primitives)
            RELAXED_ORDERING = XE_BIT(1),                   ///< driver may reorder programs and copys between barriers and
                                                            ///< synchronization primitives

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_command_list_parameter_t
        enum class command_list_parameter_t
        {
            TBD,                                            ///< TBD

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
        /// @brief C++ version for ::xe_command_list_desc_t
        struct command_list_desc_t
        {
            command_list_desc_version_t version = command_list_desc_version_t::CURRENT; ///< [in] ::COMMAND_LIST_DESC_VERSION_CURRENT
            command_list_flag_t flags = command_list_flag_t::NONE;  ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_image_region_t
        struct image_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in pixels
            uint32_t originY;                               ///< [in] The origin y offset for region in pixels
            uint32_t originZ;                               ///< [in] The origin z offset for region in pixels
            uint32_t width;                                 ///< [in] The region width relative to origin in pixels
            uint32_t height;                                ///< [in] The region height relative to origin in pixels
            uint32_t depth;                                 ///< [in] The region depth relative to origin in pixels

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_thread_group_dimensions_t
        struct thread_group_dimensions_t
        {
            uint32_t groupCountX = 0;                       ///< [in] size of thread group in X dimension
            uint32_t groupCountY = 0;                       ///< [in] size of thread group in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] size of thread group in Z dimension

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendBarrier
        /// @throws result_t
        inline void
        AppendBarrier(
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before executing
                                                            ///< barrier
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendMemoryRangesBarrier
        /// @throws result_t
        inline void
        AppendMemoryRangesBarrier(
            uint32_t numRanges,                             ///< [in] number of memory ranges
            const size_t* pRangeSizes,                      ///< [in] array of sizes of memory range
            const void** pRanges,                           ///< [in] array of memory ranges
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before executing
                                                            ///< barrier
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListCreate
        /// @returns
        ///     - ::command_list_handle_t: pointer to handle of command list object created
        /// 
        /// @throws result_t
        inline static command_list_handle_t
        Create(
            device_handle_t hDevice,                        ///< [in] handle of the device object
            const command_list_desc_t* desc                 ///< [in] pointer to command list descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListDestroy
        /// @throws result_t
        inline static void
        Destroy(
            command_list_handle_t hCommandList              ///< [in] handle of command list object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListClose
        /// @throws result_t
        inline void
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListReset
        /// @throws result_t
        inline void
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListSetParameter
        /// @throws result_t
        inline void
        SetParameter(
            command_list_parameter_t parameter,             ///< [in] parameter to change
            uint32_t value                                  ///< [in] value of attribute
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListGetParameter
        /// @returns
        ///     - uint32_t: value of attribute
        /// 
        /// @throws result_t
        inline uint32_t
        GetParameter(
            command_list_parameter_t parameter              ///< [in] parameter to retrieve
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListResetParameters
        /// @throws result_t
        inline void
        ResetParameters(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListReserveSpace
        /// @returns
        ///     - void*: pointer to command buffer space reserved
        /// 
        /// @throws result_t
        inline void*
        ReserveSpace(
            size_t size                                     ///< [in] size (in bytes) to reserve
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendMemoryCopy
        /// @throws result_t
        inline void
        AppendMemoryCopy(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size,                                    ///< [in] size in bytes to copy
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before copy
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendMemorySet
        /// @throws result_t
        inline void
        AppendMemorySet(
            void* ptr,                                      ///< [in] pointer to memory to initialize
            int value,                                      ///< [in] value to initialize memory to
            size_t size,                                    ///< [in] size in bytes to initailize
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before copy
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendImageCopy
        /// @throws result_t
        inline void
        AppendImageCopy(
            image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
            image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before copy
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendImageCopyRegion
        /// @throws result_t
        inline void
        AppendImageCopyRegion(
            image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
            image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
            image_region_t* pDstRegion = nullptr,           ///< [in][optional] destination region descriptor
            image_region_t* pSrcRegion = nullptr,           ///< [in][optional] source region descriptor
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before copy
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendImageCopyToMemory
        /// @throws result_t
        inline void
        AppendImageCopyToMemory(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
            image_region_t* pSrcRegion = nullptr,           ///< [in][optional] source region descriptor
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before copy
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendImageCopyFromMemory
        /// @throws result_t
        inline void
        AppendImageCopyFromMemory(
            image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            image_region_t* pDstRegion = nullptr,           ///< [in][optional] destination region descriptor
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before copy
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before copy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendMemoryPrefetch
        /// @throws result_t
        inline void
        AppendMemoryPrefetch(
            const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
            size_t count                                    ///< [in] size in bytes of the memory range to prefetch
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendMemAdvise
        /// @throws result_t
        inline void
        AppendMemAdvise(
            device_handle_t hDevice,                        ///< [in] device associated with the memory advice
            const void* ptr,                                ///< [in] Pointer to the start of the memory range
            size_t size,                                    ///< [in] Size in bytes of the memory range
            memory_advice_t advice                          ///< [in] Memory advice for the memory range
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendSignalEvent
        /// @throws result_t
        inline void
        AppendSignalEvent(
            event_handle_t hEvent                           ///< [in] handle of the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendWaitOnEvents
        /// @throws result_t
        inline void
        AppendWaitOnEvents(
            uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
            event_handle_t* phEvents                        ///< [in] handle of the events to wait on before continuing
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendEventReset
        /// @throws result_t
        inline void
        AppendEventReset(
            event_handle_t hEvent                           ///< [in] handle of the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendLaunchFunction
        /// @throws result_t
        inline void
        AppendLaunchFunction(
            function_handle_t hFunction,                    ///< [in] handle of the function object
            const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] launch function arguments.
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendLaunchFunctionIndirect
        /// @throws result_t
        inline void
        AppendLaunchFunctionIndirect(
            function_handle_t hFunction,                    ///< [in] handle of the function object
            const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain launch arguments
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendLaunchMultipleFunctionsIndirect
        /// @throws result_t
        inline void
        AppendLaunchMultipleFunctionsIndirect(
            uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
            const function_handle_t* phFunctions,           ///< [in] handles of the function objects
            const size_t* pNumLaunchArguments,              ///< [in] pointer to device memory location that will contain the actual
                                                            ///< number of launch arguments; must be less-than or equal-to numFunctions
            const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain a contiguous array of
                                                            ///< launch arguments
            event_handle_t hSignalEvent = nullptr,          ///< [in][optional] handle of the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            event_handle_t* phWaitEvents = nullptr          ///< [in][optional] handle of the events to wait on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeCommandListAppendLaunchHostFunction
        /// @throws result_t
        inline void
        AppendLaunchHostFunction(
            host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
            void* pUserData                                 ///< [in] pointer to user data to pass to host function.
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDLIST_HPP
