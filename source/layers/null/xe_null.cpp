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
* @file xe_null.cpp
*
******************************************************************************/
#include "xe_null.h"

namespace driver
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        deviceProperties.version = XE_DEVICE_PROPERTIES_VERSION_CURRENT;
        deviceProperties.type = XE_DEVICE_TYPE_GPU;
        deviceProperties.maxCommandQueues = 1;
        deviceProperties.numAsyncComputeEngines = 1;
        deviceProperties.numAsyncCopyEngines = 1;
        strcpy( deviceProperties.name, "Null Device" );

        computeProperties.version = XE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT;

        memoryProperties.version = XE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT;

        memoryAccessProperties.version = XE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT;

        cacheProperties.version = XE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT;

        imageProperties.version = XE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT;

        p2pProperties.version = XE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT;

        metricGroupProperties.version = XET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT;
        metricGroupProperties.metricCount = 1;
        metricGroupProperties.samplingType = static_cast<xet_metric_group_sampling_type_t>(
            XET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED | XET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED );
        metricGroupProperties.reportSize = 1;
        strcpy( metricGroupProperties.name, "Null Metric Group" );

        metricProperties.version = XET_METRIC_PROPERTIES_VERSION_CURRENT;
        metricProperties.metricType = XET_METRIC_TYPE_DURATION;
        metricProperties.resultType = XET_VALUE_TYPE_UINT32;
        strcpy( metricProperties.name, "Null Metric" );
        strcpy( metricProperties.resultUnits, "ns" );
    }
}
