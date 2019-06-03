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
* @file xe_object.h
*
******************************************************************************/
#pragma once
#include <unordered_map>
#include <mutex>

//////////////////////////////////////////////////////////////////////////
struct dditable_t
{
    xe_dditable_t   xe;
    xex_dditable_t  xex;
    xet_dditable_t  xet;
};

namespace loader
{
    //////////////////////////////////////////////////////////////////////////
    template<typename _object_t>
    class factory_t
    {
    protected:
        using object_t = _object_t;
        using handle_t = typename object_t::handle_t;

        // container for unique loader handles
        using ptr_t = std::unique_ptr < object_t >;
        using map_t = std::unordered_map < size_t, ptr_t >;

        map_t map;
        std::mutex mut;

    public:
        factory_t() = default;
        ~factory_t() = default;

        _object_t* get(
            handle_t _handle,
            dditable_t* _dditable )
        {
            std::lock_guard<std::mutex> lk( mut );

            auto key = reinterpret_cast<size_t>( _handle );
            auto ptr = std::make_unique<_object_t>( _handle, _dditable );
            auto iter = map.emplace( key, std::move( ptr ) ).first;
            return iter->second.get();
        }

        void release(
            handle_t _handle )
        {
            std::lock_guard<std::mutex> lk( mut );
            auto key = reinterpret_cast<size_t>( _handle );
            map.erase( key );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    template<typename _handle_t>
    class object_t
    {
    public:
        using handle_t = _handle_t;

        handle_t    handle;
        dditable_t* dditable;

        object_t() = delete;

        object_t( handle_t _handle, dditable_t* _dditable ) : handle( _handle ), dditable( _dditable )
        {
        }

        ~object_t() = default;
    };
}
