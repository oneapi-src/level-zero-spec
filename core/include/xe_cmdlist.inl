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
* @file xe_cmdlist.inl
*
* @brief C++ wrapper of Intel Xe Driver APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDLIST_INL
#define _XE_CMDLIST_INL
#if defined(__cplusplus)
#pragma once
#include "xe_cmdlist.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeExecutionBarrier
    inline void CommandList::EncodeExecutionBarrier(
        )
    {
        // auto result = ::xeCommandListEncodeExecutionBarrier( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeExecutionBarrier");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListDestroy
    inline void CommandList::Destroy(
        )
    {
        // auto result = ::xeCommandListDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListClose
    inline void CommandList::Close(
        )
    {
        // auto result = ::xeCommandListClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Close");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListReset
    inline void CommandList::Reset(
        )
    {
        // auto result = ::xeCommandListReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Reset");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListSetParameter
    inline void CommandList::SetParameter(
        command_list_parameter_t parameter,             ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
        )
    {
        // auto result = ::xeCommandListSetParameter( handle, parameter, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::SetParameter");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListGetParameter
    inline void CommandList::GetParameter(
        command_list_parameter_t parameter,             ///< [in] parameter to retrieve
        uint32_t* value                                 ///< [out] value of attribute
        )
    {
        // auto result = ::xeCommandListGetParameter( handle, parameter, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::GetParameter");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListResetParameters
    inline void CommandList::ResetParameters(
        )
    {
        // auto result = ::xeCommandListResetParameters( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::ResetParameters");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeCommandLists
    inline void CommandList::EncodeCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to encode
        command_list_handle_t* phCommandLists           ///< [in] list of handles of the command lists to encode for execution
        )
    {
        // auto result = ::xeCommandListEncodeCommandLists( handle, numCommandLists, phCommandLists->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeCommandLists");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeCommands
    inline void CommandList::EncodeCommands(
        command_format_t format,                        ///< [in] format of the command blob
        size_t size,                                    ///< [in] size (in bytes) of the command blob
        void* pBlob                                     ///< [in] pointer to blob of commands to encode into the command list
        )
    {
        // auto result = ::xeCommandListEncodeCommands( handle, format, size, pBlob );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeCommands");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListReserveSpace
    inline void CommandList::ReserveSpace(
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
        )
    {
        // auto result = ::xeCommandListReserveSpace( handle, size, ptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::ReserveSpace");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemoryCopy
    inline void CommandList::EncodeMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size                                     ///< [in] size in bytes to copy
        )
    {
        // auto result = ::xeCommandListEncodeMemoryCopy( handle, dstptr, srcptr, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemoryCopy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemorySet
    inline void CommandList::EncodeMemorySet(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size                                     ///< [in] size in bytes to initailize
        )
    {
        // auto result = ::xeCommandListEncodeMemorySet( handle, ptr, value, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemorySet");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopy
    inline void CommandList::EncodeImageCopy(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_handle_t hSrcImage                        ///< [in] handle of source image to copy from
        )
    {
        // auto result = ::xeCommandListEncodeImageCopy( handle, hDstImage->getHandle(), hSrcImage->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyRegion
    inline void CommandList::EncodeImageCopyRegion(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        image_region_t* pSrcRegion                      ///< [in][optional] source region descriptor
        )
    {
        // auto result = ::xeCommandListEncodeImageCopyRegion( handle, hDstImage->getHandle(), pDstRegion, hSrcImage->getHandle(), pSrcRegion );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopyRegion");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyToMemory
    inline void CommandList::EncodeImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        image_region_t* pSrcRegion                      ///< [in][optional] source region descriptor
        )
    {
        // auto result = ::xeCommandListEncodeImageCopyToMemory( handle, dstptr, hSrcImage->getHandle(), pSrcRegion );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopyToMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyFromMemory
    inline void CommandList::EncodeImageCopyFromMemory(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        const void* srcptr                              ///< [in] pointer to source memory to copy from
        )
    {
        // auto result = ::xeCommandListEncodeImageCopyFromMemory( handle, hDstImage->getHandle(), pDstRegion, srcptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopyFromMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemoryPrefetch
    inline void CommandList::EncodeMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
        size_t count                                    ///< [in] size in bytes of the memory region to prefetch
        )
    {
        // auto result = ::xeCommandListEncodeMemoryPrefetch( handle, ptr, count );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemoryPrefetch");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemAdvise
    inline void CommandList::EncodeMemAdvise(
        device_handle_t hDevice,                        ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        // auto result = ::xeCommandListEncodeMemAdvise( handle, hDevice->getHandle(), ptr, size, advice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemAdvise");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeSignalEvent
    inline void CommandList::EncodeSignalEvent(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListEncodeSignalEvent( handle, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeSignalEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeWaitOnEvent
    inline void CommandList::EncodeWaitOnEvent(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListEncodeWaitOnEvent( handle, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeWaitOnEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeEventReset
    inline void CommandList::EncodeEventReset(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListEncodeEventReset( handle, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeEventReset");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchFunction
    inline void CommandList::EncodeDispatchFunction(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const dispatch_function_arguments_t* pDispatchFuncArgs, ///< [in] dispatch function arguments.
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandListEncodeDispatchFunction( handle, hFunction->getHandle(), pDispatchFuncArgs, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchFunctionIndirect
    inline void CommandList::EncodeDispatchFunctionIndirect(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer, ///< [in] Pointer to buffer that will contain dispatch arguments.
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandListEncodeDispatchFunctionIndirect( handle, hFunction->getHandle(), pDispatchArgumentsBuffer, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchFunctionIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchHostFunction
    inline void CommandList::EncodeDispatchHostFunction(
        host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
        )
    {
        // auto result = ::xeCommandListEncodeDispatchHostFunction( handle, pfnHostFunc, pUserData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchHostFunction");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDLIST_INL
