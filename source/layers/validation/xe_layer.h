/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_layer.h
 *
 */
#pragma once
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"
#include "xe_util.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        xe_api_version_t version = XE_API_VERSION_1_0;

        bool enableParameterValidation = false;
        bool enableHandleLifetime = false;
        bool enableMemoryTracker = false;
        bool enableThreadingValidation = false;

        xe_dditable_t   xeDdiTable = {};
        xex_dditable_t  xexDdiTable = {};
        xet_dditable_t  xetDdiTable = {};

        context_t();
        ~context_t();
    };

    extern context_t context;
}
