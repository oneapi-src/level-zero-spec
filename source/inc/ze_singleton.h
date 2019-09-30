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
* @file xe_singleton.h
*
******************************************************************************/
#pragma once
#include <memory>
#include <unordered_map>
#include <mutex>

//////////////////////////////////////////////////////////////////////////
/// a abstract factory for creation of singleton objects
template<typename _singleton_t, typename _key_t>
class singleton_factory_t
{
protected:
    using singleton_t = _singleton_t;
    using key_t = typename std::conditional<std::is_pointer<_key_t>::value, size_t, _key_t>::type;

    using ptr_t = std::unique_ptr < singleton_t >;
    using map_t = std::unordered_map < key_t, ptr_t >;

    std::mutex mut; ///< lock for thread-safety
    map_t map;      ///< single instance of singleton for each unique key

    //////////////////////////////////////////////////////////////////////////
    /// extract the key from parameter list and if necessary, convert type
    template<typename... Ts>
    key_t getKey( _key_t _key, Ts&&... _params )
    {
        return reinterpret_cast<key_t>( _key );
    }

public:
    //////////////////////////////////////////////////////////////////////////
    /// default ctor/dtor
    singleton_factory_t() = default;
    ~singleton_factory_t() = default;

    //////////////////////////////////////////////////////////////////////////
    /// gets a pointer to a unique instance of singleton
    /// if no instance exists, then creates a new instance
    /// the params are forwarded to the ctor of the singleton
    /// the first parameter must be the unique identifier of the instance
    template<typename... Ts>
    _singleton_t* getInstance( Ts&&... _params )
    {
        auto key = getKey( std::forward<Ts>( _params )... );

        std::lock_guard<std::mutex> lk( mut );
        auto iter = map.find( key );

        if( map.end() == iter )
        {
            auto ptr = std::make_unique<singleton_t>( std::forward<Ts>( _params )... );
            iter = map.emplace( key, std::move( ptr ) ).first;
        }
        return iter->second.get();
    }

    //////////////////////////////////////////////////////////////////////////
    /// once the key is no longer valid, release the singleton
    void release( _key_t _key )
    {
        std::lock_guard<std::mutex> lk( mut );
        map.erase( getKey( _key ) );
    }
};
