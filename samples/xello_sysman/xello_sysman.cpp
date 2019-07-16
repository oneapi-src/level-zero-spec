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

void ShutdownDevice(xet_sysman_handle_t hSysmanDevice)
{
    struct
    {
        xet_device_prop_cold_shutdown_t shutdown;
    } data;
    xet_device_property_request_t requests[] = 
    {
        { XET_DEVICE_PROP_COLD_SHUTDOWN,    &data.shutdown, sizeof(data.shutdown) },
    };
    data.shutdown.doShutdown = 1;

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

        fprintf(stdout, "    Assets:\n");
        for (int i = 0; i < XET_ACCEL_ASSET_MAX_TYPES; i++)
        {
            if (info.assetInfo[i].numBlocks)
            {
                const char* pResName;
                xetSysmanGetAccelAssetName(hSysmanDevice, (xet_accel_asset_t)i, &pResName);
                if (info.numResourcesByType[i])
                {
                    fprintf(stdout, "        %s: %u blocks, %u engines\n", pResName, info.assetInfo[i].numBlocks, info.assetInfo[i].numEngines);
                }
            }
        }
        fprintf(stdout, "\n");
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