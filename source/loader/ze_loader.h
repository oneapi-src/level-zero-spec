/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader.h
 *
 */
#pragma once
#include <vector>

#include "ze_ddi.h"
#include "zet_ddi.h"
#include "zes_ddi.h"
#ifdef ZE_EXPERIMENTAL
#include "zex_ddi.h"
#endif

#include "ze_util.h"
#include "ze_object.h"

#include "ze_ldrddi.h"
#include "zet_ldrddi.h"
#include "zes_ldrddi.h"
#ifdef ZE_EXPERIMENTAL
#include "zex_ldrddi.h"
#endif

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
    class __zedlllocal context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_0_91;

        driver_vector_t drivers;

        HMODULE validationLayer = nullptr;

        bool forceIntercept = false;

        context_t();
        ~context_t();
    };

    extern context_t context;

}
