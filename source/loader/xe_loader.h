/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_loader.h
 *
 */
#pragma once
#include <vector>

#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"
#include "xe_util.h"

#include "xe_object.h"
#include "xe_core_loader.h"
#include "xe_experimental_loader.h"
#include "xe_tools_loader.h"

namespace loader
{
    //////////////////////////////////////////////////////////////////////////
    struct driver_t
    {
        HMODULE handle = NULL;

        dditable_t dditable = {};
    };

    using driver_vector_t = std::vector< driver_t >;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        xe_api_version_t version = XE_API_VERSION_1_0;

        driver_vector_t drivers;

        HMODULE validationLayer = nullptr;

        bool forceIntercept = false;

        context_t();
        ~context_t();
    };

    extern context_t context;

}
