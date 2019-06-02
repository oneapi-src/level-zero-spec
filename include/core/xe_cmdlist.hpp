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
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief type definition for host function pointers used with
        ///        ::CommandListAppendLaunchHostFunction
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        typedef void(__xecall *host_pfn_t)(
            void* pUserData                                 ///< [in] Pointer to user data to pass to host function.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::command_list_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command list creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = XE_BIT(0),                          ///< command list **only** contains copy operations (and synchronization
                                                            ///< primitives)
            RELAXED_ORDERING = XE_BIT(1),                   ///< driver may reorder programs and copys between barriers and
                                                            ///< synchronization primitives

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command list parameters
        enum class parameter_t
        {
            TBD,                                            ///< TBD

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory advice hints
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
        /// @brief Command List descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::COMMAND_LIST_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copy region descriptor
        struct copy_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in bytes
            uint32_t originY;                               ///< [in] The origin y offset for region in rows
            uint32_t width;                                 ///< [in] The region width relative to origin in bytes
            uint32_t height;                                ///< [in] The region height relative to origin in rows

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Region descriptor
        struct image_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in pixels
            uint32_t originY;                               ///< [in] The origin y offset for region in pixels
            uint32_t originZ;                               ///< [in] The origin z offset for region in pixels
            uint32_t width;                                 ///< [in] The region width relative to origin in pixels
            uint32_t height;                                ///< [in] The region height relative to origin in pixels
            uint32_t depth;                                 ///< [in] The region depth relative to origin. For 1D or 2D images, set
                                                            ///< this to 1.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Function thread group dimensions.
        struct thread_group_dimensions_t
        {
            uint32_t groupCountX = 0;                       ///< [in] size of thread group in X dimension
            uint32_t groupCountY = 0;                       ///< [in] size of thread group in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] size of thread group in Z dimension

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_list_handle_t m_handle;                 ///< [in] handle of command list object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command list object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandList( void ) = delete;
        CommandList( 
            command_list_handle_t handle,                   ///< [in] handle of command list object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command list object
            );

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a command list on the device for submitting commands to any
        ///        command queue.
        /// 
        /// @details
        ///     - The command list is created in the 'open' state.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* __xecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command list descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a command list on the device with an implicit command queue
        ///        for immediate submission of commands.
        /// 
        /// @details
        ///     - The command list is created in the 'open' state and never needs to be
        ///       closed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* __xecall
        CreateImmediate(
            Device* pDevice,                                ///< [in] pointer to the device object
            const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a command list.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the command list before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this command list.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __xecall
        Destroy(
            CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes a command list; ready to be executed by a command queue.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset a command list to initial (empty) state; ready for appending
        ///        commands.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the command list before it is reset
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a command list's parameter.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - cuCtxSetCacheConfig
        ///     - cuCtxSetLimit
        ///     - cuCtxSetSharedMemConfig
        /// @throws result_t
        void __xecall
        SetParameter(
            parameter_t parameter,                          ///< [in] parameter to change
            uint32_t value                                  ///< [in] value of attribute
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a command list's parameter.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - cuCtxGetCacheConfig
        ///     - cuCtxGetLimit
        ///     - cuCtxGetSharedMemConfig
        ///     - cuCtxGetStreamPriorityRange
        /// @returns
        ///     - uint32_t: value of attribute
        /// 
        /// @throws result_t
        uint32_t __xecall
        GetParameter(
            parameter_t parameter                           ///< [in] parameter to retrieve
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resets all command list parameters to default state.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        ResetParameters(
            void
            );

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

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends an execution and global memory barrier into a command list.
        /// 
        /// @details
        ///     - If numWaitEvents is zero, then all previous commands are completed
        ///       prior to the execution of the barrier.
        ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
        ///       signalled prior to the execution of the barrier.
        ///     - This command blocks all following commands from beginning until the
        ///       execution of the barrier completes.
        ///     - Memory and cache hierarchies are flushed and invalidated sufficient
        ///       for device and host access.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkCmdPipelineBarrier**
        ///     - clEnqueueBarrierWithWaitList
        /// @throws result_t
        void __xecall
        AppendBarrier(
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends a global memory ranges barrier into a command list.
        /// 
        /// @details
        ///     - If numWaitEvents is zero, then all previous commands are completed
        ///       prior to the execution of the barrier.
        ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
        ///       signalled prior to the execution of the barrier.
        ///     - This command blocks all following commands from beginning until the
        ///       execution of the barrier completes.
        ///     - Memory and cache hierarchies are flushed and invalidated sufficient
        ///       for device and host access.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        AppendMemoryRangesBarrier(
            uint32_t numRanges,                             ///< [in] number of memory ranges
            const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
            const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies host, device, or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by both srcptr and dstptr must be accessible by
        ///       the device on which the command list is created.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clEnqueueCopyBuffer**
        ///     - **clEnqueueReadBuffer**
        ///     - **clEnqueueWriteBuffer**
        ///     - **clEnqueueSVMMemcpy**
        /// @throws result_t
        void __xecall
        AppendMemoryCopy(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size,                                    ///< [in] size in bytes to copy
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Initializes host, device, or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by dstptr must be accessible by the device on
        ///       which the command list is created.
        ///     - The value to initialize memory to is interpreted as an 8-bit unsigned
        ///       char; the upper 24-bits are ignored.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clEnqueueFillBuffer**
        ///     - **clEnqueueSVMMemFill**
        /// @throws result_t
        void __xecall
        AppendMemorySet(
            void* ptr,                                      ///< [in] pointer to memory to initialize
            int value,                                      ///< [in] value to initialize memory to
            size_t size,                                    ///< [in] size in bytes to initailize
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies a region from a 2D array of host, device, or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by both srcptr and dstptr must be accessible by
        ///       the device on which the command list is created.
        ///     - The region width and height for both src and dst must be same. The
        ///       origins can be different.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        AppendMemoryCopyRegion(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            copy_region_t* dstRegion,                       ///< [in] pointer to destination region to copy to
            uint32_t dstPitch,                              ///< [in] destination pitch in bytes
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            copy_region_t* srcRegion,                       ///< [in] pointer to source region to copy from
            uint32_t srcPitch,                              ///< [in] source pitch in bytes
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies a image.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clEnqueueCopyImage**
        /// @throws result_t
        void __xecall
        AppendImageCopy(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies a region of a image to another image.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        AppendImageCopyRegion(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            image_region_t* pDstRegion = nullptr,           ///< [in][optional] destination region descriptor
            image_region_t* pSrcRegion = nullptr,           ///< [in][optional] source region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies from a image to device or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by dstptr must be accessible by the device on
        ///       which the command list is created.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clEnqueueReadImage
        /// @throws result_t
        void __xecall
        AppendImageCopyToMemory(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            image_region_t* pSrcRegion = nullptr,           ///< [in][optional] source region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies to a image from device or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by srcptr must be accessible by the device on
        ///       which the command list is created.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clEnqueueWriteImage
        /// @throws result_t
        void __xecall
        AppendImageCopyFromMemory(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            image_region_t* pDstRegion = nullptr,           ///< [in][optional] destination region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Asynchronously prefetches shared memory to the device associated with
        ///        the specified command list
        /// 
        /// @details
        ///     - This is a hint to improve performance only and is not required for
        ///       correctness.
        ///     - Only prefetching to the device associated with the specified command
        ///       list is supported.
        ///       Prefetching to the host or to a peer device is not supported.
        ///     - Prefetching may not be supported for all allocation types for all devices.
        ///       If memory prefetching is not supported for the specified memory range
        ///       the prefetch hint may be ignored.
        ///     - Prefetching may only be supported at a device-specific granularity,
        ///       such as at a page boundary.
        ///       In this case, the memory range may be expanded such that the start and
        ///       end of the range satisfy granularity requirements.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - cudaMemPrefetchAsync
        ///     - clEnqueueSVMMigrateMem
        /// @throws result_t
        void __xecall
        AppendMemoryPrefetch(
            const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
            size_t count                                    ///< [in] size in bytes of the memory range to prefetch
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Provides advice about the use of a shared memory range
        /// 
        /// @details
        ///     - Memory advice is a performance hint only and is not required for
        ///       functional correctness.
        ///     - Memory advice can be used to override driver heuristics to explicitly
        ///       control shared memory behavior.
        ///     - Not all memory advice hints may be supported for all allocation types
        ///       for all devices.
        ///       If a memory advice hint is not supported by the device it will be ignored.
        ///     - Memory advice may only be supported at a device-specific granularity,
        ///       such as at a page boundary.
        ///       In this case, the memory range may be expanded such that the start and
        ///       end of the range satisfy granularity requirements.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cudaMemAdvise**
        /// @throws result_t
        void __xecall
        AppendMemAdvise(
            Device* pDevice,                                ///< [in] device associated with the memory advice
            const void* ptr,                                ///< [in] Pointer to the start of the memory range
            size_t size,                                    ///< [in] Size in bytes of the memory range
            memory_advice_t advice                          ///< [in] Memory advice for the memory range
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends a signal of the event from the device into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clSetUserEventStatus**
        ///     - cuEventRecord
        ///     - vkCmdSetEvent
        /// @throws result_t
        void __xecall
        AppendSignalEvent(
            Event* pEvent                                   ///< [in] pointer to the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends wait on event(s) on the device into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        AppendWaitOnEvents(
            uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
            Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                            ///< continuing
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset an event back to not signaled state
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - vkResetEvent
        /// @throws result_t
        void __xecall
        AppendEventReset(
            Event* pEvent                                   ///< [in] pointer to the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch function over one or more work groups.
        /// 
        /// @details
        ///     - This may **not** be called for a command list created with
        ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuLaunchKernel**
        /// @throws result_t
        void __xecall
        AppendLaunchFunction(
            Function* pFunction,                            ///< [in] pointer to the function object
            const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] launch function arguments.
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch function over one or more work groups using indirect arguments.
        /// 
        /// @details
        ///     - The launch arguments need to be device visible.
        ///     - The launch arguments buffer may not be reusued until the function has
        ///       completed on the device.
        ///     - This may **not** be called for a command list created with
        ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuLaunchKernel**
        /// @throws result_t
        void __xecall
        AppendLaunchFunctionIndirect(
            Function* pFunction,                            ///< [in] pointer to the function object
            const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch multiple functions over one or more work groups using an array
        ///        of indirect arguments.
        /// 
        /// @details
        ///     - The array of launch arguments need to be device visible.
        ///     - The array of launch arguments buffer may not be reusued until the
        ///       function has completed on the device.
        ///     - This may **not** be called for a command list created with
        ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuLaunchKernel**
        /// @throws result_t
        void __xecall
        AppendLaunchMultipleFunctionsIndirect(
            uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
            Function** ppFunctions,                         ///< [in][range(0, numFunctions)] handles of the function objects
            const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                            ///< number of launch arguments; value must be less-than or equal-to
                                                            ///< numFunctions
            const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                            ///< contain a contiguous array of launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch host function. All work after this command in the command list
        ///        will block until host function completes.
        /// 
        /// @details
        ///     - This may **not** be called for a command list created with
        ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **cuLaunchHostFunc**
        /// @throws result_t
        void __xecall
        AppendLaunchHostFunction(
            host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
            void* pUserData,                                ///< [in] pointer to user data to pass to host function.
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

    };

} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandList::desc_version_t to std::string
std::string to_string( xe::CommandList::desc_version_t val );

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandList::flag_t to std::string
std::string to_string( xe::CommandList::flag_t val );

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandList::parameter_t to std::string
std::string to_string( xe::CommandList::parameter_t val );

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts CommandList::memory_advice_t to std::string
std::string to_string( xe::CommandList::memory_advice_t val );


#endif // _DEBUG
#endif // defined(__cplusplus)
#endif // _XE_CMDLIST_HPP
