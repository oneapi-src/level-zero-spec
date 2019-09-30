/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_lib.h
 *
 */
#pragma once
#include "zet_api.hpp"
#include "zet_ddi.h"
#include "ze_util.h"
#include "ze_singleton.h"
#include <vector>

namespace zet_lib
{
    using metric_group_factory_t = singleton_factory_t<zet::MetricGroup, zet::metric_group_handle_t>;
    using metric_factory_t = singleton_factory_t<zet::Metric, zet::metric_handle_t>;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        ze_result_t Init();

        zet_dditable_t  ddiTable = {};

        metric_group_factory_t  metricGroupFactory;
        metric_factory_t        metricFactory;
    };

    extern context_t context;

} // namespace zet_lib
