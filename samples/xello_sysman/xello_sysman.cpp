/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "xello_sysman.h"

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "xet_api.h"

void ShowRasCounters(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRas;
    xet_ras_filter_t filter = XET_RAS_FILTER_ALL_COUNTERS;
    if (xetSysmanGetRasErrors(hSysmanDevice, &filter, false, &numRas, NULL) == XE_RESULT_SUCCESS)
    {
        xet_ras_error_t* pCounters = (xet_ras_error_t*)malloc(numRas * sizeof(xet_ras_error_t));

        if (xetSysmanGetRasErrors(hSysmanDevice, &filter, false, &numRas, pCounters) == XE_RESULT_SUCCESS)
        {
            for (uint32_t i = 0; i < numRas; i++)
            {
                fprintf(stdout, "RAS error %s: value=%llu\n",
                    pCounters[i].pName, pCounters[i].data);
            }
        }
    }
}

void LocalMemoryRasConfig(xet_sysman_handle_t hSysmanDevice)
{
    xet_ras_config_t config;
    if (xetSysmanGetRasConfig(hSysmanDevice, &config) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Local memory:\n");
        if (config.numRas)
        {
            fprintf(stdout, "    RAS support: yes\n");
            fprintf(stdout, "    RAS enabled: %s\n", (config.enabled & XET_RAS_ERROR_LOC_MAIN_MEM) ? "yes" : "no");
        }
        else
        {
            fprintf(stdout, "    RAS support: no\n");
        }
    }
}

void ResetDevice(xet_sysman_handle_t hSysmanDevice)
{
    if (xetSysmanDeviceReset(hSysmanDevice))
    {
        fprintf(stdout, "Device reset initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem resetting the device.\n");
    }
}

void GetFreqIntervals(xet_sysman_handle_t hSysmanDevice)
{
    xet_resprop_info_t info[] =
    {
        { XET_RESPROP_FREQ_RANGE },
        { XET_RESPROP_FREQ_RESOLVED_FREQ },
    };
    if (xetSysmanGetPropertyInfo(hSysmanDevice, sizeof(info) / sizeof(info[0]), info) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Frequency update interval: %u microseconds\n", info[0].minSetInterval);
        fprintf(stdout, "Frequency sample interval: %u microseconds\n", info[1].minGetInterval);
    }
}

bool HaveFanControl(xet_sysman_handle_t hSysmanDevice)
{
    bool ret = false;
    xet_resprop_info_t info;
    info.property = XET_RESPROP_FAN_FIXED_SPEED;
    if (xetSysmanGetPropertyInfo(hSysmanDevice, 1, &info) == XE_RESULT_SUCCESS)
    {
        if ((info.support & XET_PROP_SUPPORT_DEVICE) &&
            (info.access & XET_PROP_ACCESS_WRITE_PERMISSIONS))
        {
            ret = true;
        }
    }
    return ret;
}

void ShowFanInfo(xet_sysman_handle_t hSysmanDevice, xet_resid_t FanId)
{
    struct FanData
    {
        xet_resprop_fan_speed_rpm_t        speedRpm;
        xet_resprop_fan_speed_percent_t    speedPercent;
    };

    FanData data;
    xet_resprop_request_t requests[] = 
    {
        { FanId, XET_RESPROP_FAN_SPEED_RPM,       &data.speedRpm,       sizeof(data.speedRpm) },
        { FanId, XET_RESPROP_FAN_SPEED_PERCENT,   &data.speedPercent,   sizeof(data.speedPercent) },
    };

    xe_result_t res = xetSysmanGetProperties(
        hSysmanDevice,
        sizeof(requests) / sizeof(requests[0]),
        requests);

    if ((res == XE_RESULT_SUCCESS) || (res == XE_RESULT_ERROR_UNKNOWN))
    {
        if (requests[0].status == XE_RESULT_SUCCESS)
        {
            fprintf(stdout, "        Fan %u: speed = %u rpm\n", FanId, data.speedRpm.speed);
        }
        else
        {
            fprintf(stderr, "        Fan %u: error reading XET_RESPROP_FAN_SPEED_RPM\n", FanId);
        }
        if (requests[1].status == XE_RESULT_SUCCESS)
        {
            fprintf(stdout, "        Fan %u: speed = %u %%\n", FanId, data.speedPercent.speed);
        }
        else
        {
            fprintf(stderr, "        Fan %u: error reading XET_RESPROP_FAN_SPEED_PERCENT\n", FanId);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Can't request data.\n");
    }
}

void CheckResources(xet_sysman_handle_t hSysmanDevice)
{
    xet_resid_info_t resources [] =
    {
        { XET_RESID_UTIL_GPU },
        { XET_RESID_UTIL_COMPUTE },
        { XET_RESID_UTIL_MEDIA },
        { XET_RESID_UTIL_VIDEO_DECODE },
        { XET_RESID_UTIL_VIDEO_ENCODE }
    };
    uint32_t count = sizeof(resources) / sizeof(resources[0]);
    if (xetSysmanGetResourceInfo(hSysmanDevice, count, resources) == XE_RESULT_SUCCESS)
    {
        for (uint32_t i = 0; i < count; i++)
        {
            fprintf(stdout, "Resource %d: %s = %s\n", resources[i].id, resources[i].pName, resources[i].available ? "supported" : "not supported");
        }
    }
}

void ShowAllResources(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numResources;
    if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_ANY, &numResources, NULL) == XE_RESULT_SUCCESS)
    {
        if (numResources)
        {
            xet_resid_info_t* pInfo = (xet_resid_info_t*)malloc(numResources * sizeof(xet_resid_info_t));
            if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_ANY, &numResources, pInfo) == XE_RESULT_SUCCESS)
            {
                for (uint32_t i = 0; i < numResources; i++)
                {
                    fprintf(stdout, "Resource %d: %s = %s\n", pInfo->id, pInfo->pName, pInfo->pDesc);
                }
            }
            free(pInfo);
        }
    }
}

void ShowFans(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_FAN, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        if (numFans)
        {
            xet_resid_info_t* pInfo = (xet_resid_info_t*)malloc(numFans * sizeof(xet_resid_info_t));
            if (xetSysmanGetResources(hSysmanDevice, XET_RESOURCE_TYPE_FAN, &numFans, pInfo) == XE_RESULT_SUCCESS)
            {
                for (uint32_t i = 0; i < numFans; i++)
                {
                    fprintf(stdout, "    Fan %s\n", pInfo->pName);
                    ShowFanInfo(hSysmanDevice, pInfo->id);
                }
            }
            free(pInfo);
        }
    }
}

void ShowInventoryInfo(xet_sysman_handle_t hSysmanDevice)
{
    struct InventoryData
    {
        xet_resprop_dev_serial_number_t  SerialNumber;
        xet_resprop_dev_board_number_t   BoardNumber;
    };

    InventoryData data;
    xet_resprop_request_t requests[] = 
    {
        { XET_RESID_DEV_INVENTORY, XET_RESPROP_DEV_SERIAL_NUMBER,    &data.SerialNumber, sizeof(data.SerialNumber) },
        { XET_RESID_DEV_INVENTORY, XET_RESPROP_DEV_BOARD_NUMBER,     &data.BoardNumber,  sizeof(data.BoardNumber)  },
    };

    if (xetSysmanGetProperties(
        hSysmanDevice,
        sizeof(requests) / sizeof(requests[0]),
        requests) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Serial#: %s\n", data.SerialNumber.str);
        fprintf(stdout, "    Board#:  %s\n", data.BoardNumber.str);
    }
}

void ShowDeviceInfo(xet_sysman_handle_t hSysmanDevice)
{
    ShowInventoryInfo(hSysmanDevice);

    ShowFans(hSysmanDevice);
}

int gNumDevices = 0;

int ListDevices(xe_device_group_handle_t hDeviceGroup); // Forward declaration

int main( int argc, char *argv[] )
{
    int ret = -1;
    if ( (xeInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) ||
         (xetInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t groupCount = 0;
        xeDeviceGroupGet(&groupCount, nullptr);
        xe_device_group_handle_t* allDeviceGroups = (xe_device_group_handle_t*)
            malloc(groupCount * sizeof(xe_device_group_handle_t));
        xeDeviceGroupGet(&groupCount, allDeviceGroups);
        // Find the first GPU device group
        xe_device_group_handle_t hDeviceGroup = nullptr;
        for(uint32_t i = 0; i < groupCount; ++i)
        {
            xe_device_properties_t device_properties;
            xeDeviceGroupGetDeviceProperties(allDeviceGroups[i], &device_properties);
            if(XE_DEVICE_TYPE_GPU == device_properties.type)
            {
                if ((ret = ListDevices(allDeviceGroups[i])) != 0)
                {
                    break;
                }
            }
        }

        free(allDeviceGroups);
    }

    if (gNumDevices == 0)
    {
        fprintf(stdout, "No managed devices found.\n");
    }

    return ret;
}

int ListDevices(xe_device_group_handle_t hDeviceGroup)
{
    int ret = 0;
    uint32_t deviceCount = 0;
    if (xeDeviceGet(hDeviceGroup, &deviceCount, nullptr) == XE_RESULT_SUCCESS)
    {
        if (deviceCount)
        {
            xe_device_handle_t* allDevices = (xe_device_handle_t*)
                malloc(deviceCount * sizeof(xe_device_handle_t));
            xeDeviceGet(hDeviceGroup, &deviceCount, allDevices);

            for (uint32_t i = 0; i < deviceCount; ++i)
            {
                xet_sysman_handle_t hSysmanDevice;
                xe_result_t res = xetSysmanGet(allDevices[i], XET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
                if (res == XE_RESULT_SUCCESS)
                {
                    gNumDevices++;

                    fprintf(stdout, "Device %d\n", gNumDevices);

                    ShowDeviceInfo(hSysmanDevice);
                }
                else
                {
                    fprintf(stderr, "ERROR: Can't initialize system resource management for this device.\n");
                    ret++;
                }
            }

            free(allDevices);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Couldn't get list of devices in a device group.\n");
        ret = 1;
    }

    return ret;
}
