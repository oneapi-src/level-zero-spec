/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_object.h
 *
 */
#pragma once
#include "xe_singleton.h"

//////////////////////////////////////////////////////////////////////////
struct dditable_t
{
    xe_dditable_t   xe;
    xex_dditable_t  xex;
    xet_dditable_t  xet;
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

    object_t( handle_t _handle, dditable_t* _dditable )
        : handle( _handle ), dditable( _dditable )
    {
    }

    ~object_t() = default;
};
