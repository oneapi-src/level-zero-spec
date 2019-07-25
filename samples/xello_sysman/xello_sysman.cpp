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

int gNumDevices = 0;

void ShowRasCounters(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if ((xetSysmanGetInfo(hSysmanDevice, &info) == XE_RESULT_SUCCESS) && (info.numRas))
    {
        xet_ras_filter_t filter = XET_RAS_FILTER_ALL_COUNTERS;
        xet_ras_error_t* pCounters = (xet_ras_error_t*)malloc(info.numRas * sizeof(xet_ras_error_t));

        if (xetSysmanGetRasErrors(hSysmanDevice, &filter, false, &info.numRas, pCounters) == XE_RESULT_SUCCESS)
        {
            for (uint32_t i = 0; i < info.numRas; i++)
            {
                fprintf(stdout, "RAS error %d: type=0x%x loc=0x%x resource=%d,%u value=%llu\n",
                    i, pCounters[i].type, pCounters[i].loc, pCounters[i].resourceId.type, pCounters[i].resourceId.index, pCounters[i].data);
            }
        }
    }
}

void LocalMemoryRasConfig(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if (xetSysmanGetInfo(hSysmanDevice, &info) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Local memory:\n");
        if (info.rasLocations & XET_RAS_ERROR_LOC_MAIN_MEM)
        {
            uint32_t enabled;
            fprintf(stdout, "    RAS support: yes\n");
            if (xetSysmanRasSetup(hSysmanDevice, 0, 0, &enabled) == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "    RAS enabled: %s\n", (enabled & XET_RAS_ERROR_LOC_MAIN_MEM) ? "yes" : "no");
            }
        }
        else
        {
            fprintf(stdout, "    RAS support: no\n");
        }
    }
}

void MediaUtilizationResources(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if (xetSysmanGetInfo(hSysmanDevice, &info) == XE_RESULT_SUCCESS)
    {
        const uint64_t mediaAssetBitfield = (XET_ACCEL_ASSET_VIDEO_DECODER | XET_ACCEL_ASSET_VIDEO_ENCODER | XET_ACCEL_ASSET_VIDEO_PROCESSING);
        struct
        {
            xet_accel_prop_accel_assets_t assets;
        } data;
        xet_accel_property_request_t request{ 0, XET_ACCEL_PROP_ACCEL_ASSETS, &data.assets, sizeof(data.assets) };

        fprintf(stdout, "Accelerator asset resources counting only media utilization:\n");
        for (uint32_t i = 0; i < info.numResourcesByType[XET_RESOURCE_TYPE_ACCEL]; i++)
        {
            request.index = i;
            if (xetSysmanGetAccelProperties(hSysmanDevice, 1, &request) == XE_RESULT_SUCCESS)
            {
                if ((data.assets.assets & mediaAssetBitfield) == mediaAssetBitfield)
                {
                    fprintf(stdout, "    index=%u: assets=0x%llx\n", i, data.assets.assets);
                }
            }
        }
    }
}

void ResetDevice(xet_sysman_handle_t hSysmanDevice)
{
    struct
    {
        xet_device_prop_reset_t reset;
    } data;
    xet_device_property_request_t requests[] = 
    {
        { XET_DEVICE_PROP_RESET,    &data.reset, sizeof(data.reset) },
    };
    data.reset.doReset = 1;

    if (xetSysmanSetDeviceProperties(
        hSysmanDevice,
        sizeof(requests) / sizeof(requests[0]),
        requests) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Device shutdown initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem shutting down the device.\n");
    }
}

bool HaveFanControl(xet_sysman_handle_t hSysmanDevice)
{
    bool ret = false;
    xet_fan_prop_capability_t cap;
    cap.property = XET_FAN_PROP_FIXED_SPEED;
    if (xetSysmanAvailableFanProperties(hSysmanDevice, 1, &cap) == XE_RESULT_SUCCESS)
    {
        if ((cap.support & XET_PROP_SUPPORT_DEVICE) &&
            (cap.access & XET_PROP_ACCESS_WRITE_PERMISSIONS))
        {
            ret = true;
        }
    }
    return ret;
}

void ShowFanInfo(xet_sysman_handle_t hSysmanDevice, uint32_t FanIndex)
{
    struct FanData
    {
        xet_fan_prop_speed_rpm_t        speedRpm;
        xet_fan_prop_speed_percent_t    speedPercent;
    };

    FanData data;
    xet_fan_property_request_t requests[] = 
    {
        { FanIndex, XET_FAN_PROP_SPEED_RPM,       &data.speedRpm,       sizeof(data.speedRpm) },
        { FanIndex, XET_FAN_PROP_SPEED_PERCENT,   &data.speedPercent,   sizeof(data.speedPercent) },
    };

    if (xetSysmanGetFanProperties(
        hSysmanDevice,
        sizeof(requests) / sizeof(requests[0]),
        requests) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "        Fan %u: %u rpm (%u %%)\n", FanIndex, data.speedRpm.speed, data.speedPercent.speed);
    }
}

void ShowInventoryInfo(xet_sysman_handle_t hSysmanDevice)
{
    struct DeviceData
    {
        xet_device_prop_serial_number_t  SerialNumber;
        xet_device_prop_board_number_t   BoardNumber;
    };

    DeviceData data;
    xet_device_property_request_t requests[] = 
    {
        { XET_DEVICE_PROP_SERIAL_NUMBER,    &data.SerialNumber, sizeof(data.SerialNumber) },
        { XET_DEVICE_PROP_BOARD_NUMBER,     &data.BoardNumber,  sizeof(data.BoardNumber)  },
    };

    if (xetSysmanGetDeviceProperties(
        hSysmanDevice,
        sizeof(requests) / sizeof(requests[0]),
        requests) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Serial#: %s\n", data.SerialNumber.str);
        fprintf(stdout, "    Board#:  %s\n", data.BoardNumber.str);
    }
}

void ShowAcceleratorAssets(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if (xetSysmanGetInfo(hSysmanDevice, &info) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Assets:\n");
        for (int i = 0; i < XET_ACCEL_ASSET_MAX_TYPES; i++)
        {
            if (info.numAssets[i])
            {
                const char* pAssetName;
                xetSysmanGetAccelAssetName(hSysmanDevice, (xet_accel_asset_t)i, &pAssetName);
                fprintf(stdout, "        %s: %u\n", pAssetName, info.numAssets[i]);
            }
        }
        fprintf(stdout, "\n");
    }
}

void ShowDeviceInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_info_t info;
    if (xetSysmanGetInfo(hSysmanDevice, &info) == XE_RESULT_SUCCESS)
    {
        gNumDevices++;

        fprintf(stdout, "Device %d\n", gNumDevices);

        ShowInventoryInfo(hSysmanDevice);

        fprintf(stdout, "    Num fans:                %u\n", info.numResourcesByType[XET_RESOURCE_TYPE_FAN]);
        fprintf(stdout, "    Num temperature sensors: %u\n", info.numResourcesByType[XET_RESOURCE_TYPE_TEMP]);
        fprintf(stdout, "    Num power domains:       %u\n", info.numResourcesByType[XET_RESOURCE_TYPE_PWR]);
        fprintf(stdout, "    Num frequency domains:   %u\n", info.numResourcesByType[XET_RESOURCE_TYPE_FREQ]);
        
        if (info.numResourcesByType[XET_RESOURCE_TYPE_FAN])
        {
            fprintf(stdout, "    Fans:\n");
            for (uint32_t i = 0; i < info.numResourcesByType[XET_RESOURCE_TYPE_FAN]; i++)
            {
                ShowFanInfo(hSysmanDevice, i);
            }
        }

        ShowAcceleratorAssets(hSysmanDevice);
    }
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
                xe_result_t res = xetSysmanCreate(allDevices[i], XET_SYSMAN_VERSION_CURRENT, XET_SYSMAN_INIT_FLAGS_WRITE, &hSysmanDevice);
                if (res == XE_RESULT_SUCCESS)
                {
                    if (xetSysmanDestroy(hSysmanDevice) == XE_RESULT_SUCCESS)
                    {
                        ShowDeviceInfo(hSysmanDevice);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Problem freeing system resource management for this device.\n");
                    }
                }
                else if (res == XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS)
                {
                    fprintf(stderr, "ERROR: Don't have permissions to control this device.\n");
                    ret++;
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