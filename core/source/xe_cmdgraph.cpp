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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hDevice
///         + nullptr for desc
///         + nullptr for phCommandGraph
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
    // @todo: check_return(xe_device_handle_t() == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == desc, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(XE_COMMAND_GRAPH_DESC_VERSION <= desc->version, XE_RESULT_ERROR_UNSUPPORTED);
    // @todo: check_return(nullptr == phCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphDestroy(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to destroy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Adds an edge between two command lists to the command graph.
/// 
/// @details
///     - The command graph maintains a const-reference to an existing command
///       list
///     - The application is responsible for making sure a command list is not
///       destroyed while the command graph still references
///     - The application may **not** call this function from simultaneous
///       threads with the same command graph handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
///         + hCommandGraph is closed
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphAddEdge(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of command graph object to add an edge
    xe_command_list_handle_t hProducerCommandList,  ///< [in] handle of command list object producing dependency
    xe_command_list_handle_t hConsumerCommandList   ///< [in] handle of command list object consuming dependency
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_command_list_handle_t() == hProducerCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_command_list_handle_t() == hConsumerCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Removes an edge between two command lists to the command graph.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command graph handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
///         + hCommandGraph is closed
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphRemoveEdge(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of command graph object to remove an edge
    xe_command_list_handle_t hProducerCommandList,  ///< [in] handle of command list object producing dependency
    xe_command_list_handle_t hConsumerCommandList   ///< [in] handle of command list object consuming dependency
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_command_list_handle_t() == hProducerCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(xe_command_list_handle_t() == hConsumerCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphClose(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to close
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

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
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphReset(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to reset
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the number of compute command list batches to be enqueued.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
///         + nullptr for pNumBatches
///         + hCommandGraph is not closed
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphGetComputeBatchCount(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of command graph object
    uint32_t* pNumBatches                           ///< [out] the number of batches
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pNumBatches, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the list of compute command lists in optimal execution order.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
///         + hCommandGraph is not closed
///         + invalid value for batchIndex
///         + nullptr for pCommandQueueIndex
///         + nullptr for pNumCommandLists
///         + nullptr for pphCommandLists
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphGetComputeCommandListBatch(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of command graph object
    uint32_t batchIndex,                            ///< [in] the index of the batch
    uint32_t* pCommandQueueIndex,                   ///< [out] the index of the command queue for asynchronous execution
    uint32_t* pNumCommandLists,                     ///< [out] the number of command lists in the returned list
    xe_command_list_handle_t** pphCommandLists      ///< [out] pointer to list of ordered command list handles
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pCommandQueueIndex, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pNumCommandLists, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pphCommandLists, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the number of copy-only command list batches to be enqueued.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
///         + nullptr for pNumBatches
///         + hCommandGraph is not closed
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphGetCopyBatchCount(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of command graph object
    uint32_t* pNumBatches                           ///< [out] the number of batches
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pNumBatches, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the list of copy-only command lists in optimal execution
///        order.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid handle for hCommandGraph
///         + hCommandGraph is not closed
///         + invalid value for batchIndex
///         + nullptr for pCommandQueueIndex
///         + nullptr for pNumCommandLists
///         + nullptr for pphCommandLists
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandGraphGetCopyCommandListBatch(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of command graph object
    uint32_t batchIndex,                            ///< [in] the index of the batch
    uint32_t* pCommandQueueIndex,                   ///< [out] the index of the command queue for asynchronous execution
    uint32_t* pNumCommandLists,                     ///< [out] the number of command lists in the returned list
    xe_command_list_handle_t** pphCommandLists      ///< [out] pointer to list of ordered command list handles
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(xe_command_graph_handle_t() == hCommandGraph, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pCommandQueueIndex, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pNumCommandLists, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == pphCommandLists, XE_RESULT_ERROR_INVALID_PARAMETER);

    // @todo: insert <code> here

    return XE_RESULT_SUCCESS;
}

