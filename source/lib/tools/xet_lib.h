/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_lib.h
 *
 */
#pragma once
#include "xet_api.hpp"
#include "xet_ddi.h"
#include "xe_util.h"
#include "xe_singleton.h"
#include <vector>

namespace xet_lib
{
    using metric_group_factory_t = singleton_factory_t<xet::MetricGroup, xet::metric_group_handle_t>;
    using metric_factory_t = singleton_factory_t<xet::Metric, xet::metric_handle_t>;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        xe_result_t Init();

        xet_dditable_t  ddiTable = {};

        metric_group_factory_t  metricGroupFactory;
        metric_factory_t        metricFactory;
    };

    extern context_t context;

} // namespace xet_lib
