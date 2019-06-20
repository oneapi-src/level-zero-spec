/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_null.h
 *
 */
#pragma once
#include <stdlib.h>
#include <vector>
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"
#include "xe_util.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        xe_api_version_t version = XE_API_VERSION_1_0;

        xe_dditable_t   xeDdiTable = {};
        xex_dditable_t  xexDdiTable = {};
        xet_dditable_t  xetDdiTable = {};

        context_t();
        ~context_t() = default;

        void* get( void )
        {
            static uint64_t count = 0x80800000;
            return reinterpret_cast<void*>( ++count );
        }
    };

    extern context_t context;
} // namespace driver

namespace instrumented
{
    //////////////////////////////////////////////////////////////////////////
    struct tracer_data_t
    {
        bool enabled = false;

        void* globalUserData = nullptr;

        xe_callbacks_t xePrologueCbs = {};
        xe_callbacks_t xeEpilogueCbs = {};

        xex_callbacks_t xexPrologueCbs = {};
        xex_callbacks_t xexEpilogueCbs = {};
    };

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        bool enableTracing = false;
        std::vector< tracer_data_t > tracerData;

        context_t();
        ~context_t() = default;
    };

    extern context_t context;
} // namespace instrumented
