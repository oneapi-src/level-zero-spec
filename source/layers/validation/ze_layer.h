/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_layer.h
 *
 */
#pragma once
#include "ze_ddi.h"
#include "zet_ddi.h"
#ifdef ZE_EXPERIMENTAL
#include "zex_ddi.h"
#endif
#include "ze_util.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    class __zedlllocal context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_0_91;

        bool enableParameterValidation = false;
        bool enableHandleLifetime = false;
        bool enableMemoryTracker = false;
        bool enableThreadingValidation = false;

        ze_dditable_t   zeDdiTable = {};
        zet_dditable_t  zetDdiTable = {};
#ifdef ZE_EXPERIMENTAL
        zex_dditable_t   zexDdiTable = {};
#endif

        context_t();
        ~context_t();
    };

    extern context_t context;
}
