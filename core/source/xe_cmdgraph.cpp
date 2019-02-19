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
* @file xe_cmdgraph.cpp
*
* @brief Intel Xe Driver APIs for CommandGraph
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/cmdgraph.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_cmdgraph.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command graph on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - This function may be called from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + ::XE_COMMAND_GRAPH_DESC_VERSION <= desc->version
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeDeviceCreateCommandGraph(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_graph_desc_t* desc,            ///< [in] pointer to command graph descriptor
    xe_command_graph_handle_t* phCommandGraph       ///< [out] pointer to handle of command graph object created
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == phCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_COMMAND_GRAPH_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    /// @begin {3b85e08ac6895a0dec2d64fbfb9c2e5ff0dc065fc10cfdf4e13e2903a6f626ca}

    // @todo: insert <code> here

    /// @end   {3b85e08ac6895a0dec2d64fbfb9c2e5ff0dc065fc10cfdf4e13e2903a6f626ca}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command graph.
/// 
/// @details
///     - The implementation of this function will immediately free all Host
///       allocations associated with this command graph.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphDestroy(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {ca29e107ea24beb8541932fc6be7c98805f20ced8106a62fc76cfa3381110226}

    // @todo: insert <code> here

    /// @end   {ca29e107ea24beb8541932fc6be7c98805f20ced8106a62fc76cfa3381110226}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command graph; ready to be enqueued into a command queue.
/// 
/// @details
///     - The command graph will optimize the execution order of the command
///       lists.
///     - A command list may **not** be reset after the command graph is closed.
///     - The application may **not** call this function from simultaneous
///       threads with the same command graph handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphClose(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to close
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {85412d12c54a9c3632a9e390efce8ad3ad8fbccc1401d7970387baa3b197c3da}

    // @todo: insert <code> here

    /// @end   {85412d12c54a9c3632a9e390efce8ad3ad8fbccc1401d7970387baa3b197c3da}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command graph to initial (empty) state; ready for adding
///        command lists.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command graph handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandGraph
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphReset(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to reset
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {528e83125c070c5e70c5fd5f376cb08b0feb42d3b1b83e7fc7eb656c2277e709}

    // @todo: insert <code> here

    /// @end   {528e83125c070c5e70c5fd5f376cb08b0feb42d3b1b83e7fc7eb656c2277e709}
    return XE_RESULT_SUCCESS;
}

