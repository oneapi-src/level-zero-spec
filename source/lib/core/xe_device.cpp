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
* @file xe_device.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/device.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"
#include "xe_api.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Device::Device( 
        Driver* pDriver                                 ///< [in] pointer to parent object
        ) :
        m_pDriver( pDriver )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reports the number of devices
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetCount**
    /// 
    /// @returns
    ///     - uint32_t: number of devices available
    /// 
    /// @throws result_t
    uint32_t __xecall
    Device::GetCount(
        void
        )
    {
        // auto result = ::xeDeviceGetCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetCount");

        return uint32_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns a handle to the device object
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGet**
    ///     - clGetDeviceIDs
    /// 
    /// @returns
    ///     - Device: pointer to handle of device object created
    /// 
    /// @throws result_t
    Device* __xecall
    Device::Get(
        uint32_t ordinal                                ///< [in] The device index in the range of [0, ::DeviceGetCount]
        )
    {
        // auto result = ::xeDeviceGet( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::Get");

        return (Device*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns a handle to the sub-device object
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGet**
    ///     - clGetDeviceIDs
    /// 
    /// @returns
    ///     - Device: pointer to handle of sub-device object.
    /// 
    /// @throws result_t
    Device* __xecall
    Device::GetSubDevice(
        uint32_t ordinal                                ///< [in] ordinal of sub-device to retrieve
        )
    {
        // auto result = ::xeDeviceGetSubDevice( handle, ordinal );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetSubDevice");

        return (Device*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the API version supported by the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuCtxGetApiVersion**
    /// 
    /// @returns
    ///     - api_version_t: api version
    /// 
    /// @throws result_t
    Device::api_version_t __xecall
    Device::GetApiVersion(
        void
        )
    {
        // auto result = ::xeDeviceGetApiVersion( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetApiVersion");

        return api_version_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - cuDeviceGetName
    ///     - clGetDeviceInfo
    /// 
    /// @returns
    ///     - properties_t: query result for device properties
    /// 
    /// @throws result_t
    Device::properties_t __xecall
    Device::GetProperties(
        void
        )
    {
        // auto result = ::xeDeviceGetProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetProperties");

        return properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves compute attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - clGetDeviceInfo
    /// 
    /// @returns
    ///     - compute_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    Device::compute_properties_t __xecall
    Device::GetComputeProperties(
        void
        )
    {
        // auto result = ::xeDeviceGetComputeProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetComputeProperties");

        return compute_properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves memory attributes of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetAttribute**
    ///     - cuDeviceTotalMem
    ///     - clGetDeviceInfo
    /// 
    /// @returns
    ///     - memory_properties_t: query result for compute properties
    /// 
    /// @throws result_t
    Device::memory_properties_t __xecall
    Device::GetMemoryProperties(
        void
        )
    {
        // auto result = ::xeDeviceGetMemoryProperties( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetMemoryProperties");

        return memory_properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves Peer-to-Peer properties between one device and a peer
    ///        devices
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaDeviceGetP2PAttribute**
    /// 
    /// @returns
    ///     - p2p_properties_t: Peer-to-Peer properties between source and peer device
    /// 
    /// @throws result_t
    Device::p2p_properties_t __xecall
    Device::GetP2PProperties(
        Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
        )
    {
        // auto result = ::xeDeviceGetP2PProperties( handle, pPeerDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::GetP2PProperties");

        return p2p_properties_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries if one device can directly access peer device allocations
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaDeviceCanAccessPeer**
    /// 
    /// @returns
    ///     - bool_t: returned access capability
    /// 
    /// @throws result_t
    bool_t __xecall
    Device::CanAccessPeer(
        Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
        )
    {
        // auto result = ::xeDeviceCanAccessPeer( handle, pPeerDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::CanAccessPeer");

        return bool_t{};
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Intermediate cache configuration for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFuncSetCacheConfig **
    /// 
    /// @throws result_t
    void __xecall
    Device::SetIntermediateCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        // auto result = ::xeDeviceSetIntermediateCacheConfig( handle, CacheConfig );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SetIntermediateCacheConfig");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred Last Level cache configuration for a device.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaFuncSetCacheConfig **
    /// 
    /// @throws result_t
    void __xecall
    Device::SetLastLevelCacheConfig(
        cache_config_t CacheConfig                      ///< [in] CacheConfig
        )
    {
        // auto result = ::xeDeviceSetLastLevelCacheConfig( handle, CacheConfig );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::SetLastLevelCacheConfig");
    }

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::api_version_t to std::string
    std::string to_string( Device::api_version_t val )
    {
        switch( val )
        {
        case Device::api_version_t::_1_0:
            return std::string("Device::api_version_t::_1_0");
        };
        return std::string("Device::api_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_version_t to std::string
    std::string to_string( Device::properties_version_t val )
    {
        switch( val )
        {
        case Device::properties_version_t::CURRENT:
            return std::string("Device::properties_version_t::CURRENT");
        };
        return std::string("Device::properties_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_version_t to std::string
    std::string to_string( Device::compute_properties_version_t val )
    {
        switch( val )
        {
        case Device::compute_properties_version_t::CURRENT:
            return std::string("Device::compute_properties_version_t::CURRENT");
        };
        return std::string("Device::compute_properties_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_version_t to std::string
    std::string to_string( Device::memory_properties_version_t val )
    {
        switch( val )
        {
        case Device::memory_properties_version_t::CURRENT:
            return std::string("Device::memory_properties_version_t::CURRENT");
        };
        return std::string("Device::memory_properties_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_capabilities_t to std::string
    std::string to_string( Device::memory_access_capabilities_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_ACCESS) & bits )
            str += "Device::memory_access_capabilities_t::MEMORY_ACCESS | ";
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_ATOMIC_ACCESS) & bits )
            str += "Device::memory_access_capabilities_t::MEMORY_ATOMIC_ACCESS | ";
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_CONCURRENT_ACCESS) & bits )
            str += "Device::memory_access_capabilities_t::MEMORY_CONCURRENT_ACCESS | ";
        if( static_cast<uint32_t>(Device::memory_access_capabilities_t::MEMORY_CONCURRENT_ATOMIC_ACCESS) & bits )
            str += "Device::memory_access_capabilities_t::MEMORY_CONCURRENT_ATOMIC_ACCESS | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_version_t to std::string
    std::string to_string( Device::p2p_properties_version_t val )
    {
        switch( val )
        {
        case Device::p2p_properties_version_t::CURRENT:
            return std::string("Device::p2p_properties_version_t::CURRENT");
        };
        return std::string("Device::p2p_properties_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_config_t to std::string
    std::string to_string( Device::cache_config_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(Device::cache_config_t::DEFAULT) & bits )
            str += "Device::cache_config_t::DEFAULT | ";
        if( static_cast<uint32_t>(Device::cache_config_t::LARGE_SLM) & bits )
            str += "Device::cache_config_t::LARGE_SLM | ";
        if( static_cast<uint32_t>(Device::cache_config_t::LARGE_DATA) & bits )
            str += "Device::cache_config_t::LARGE_DATA | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }


#endif // _DEBUG
} // namespace xe
