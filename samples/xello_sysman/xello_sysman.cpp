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

void PrintRasDetails(xet_ras_details_t* pDetails)
{
    fprintf(stdout, "    Number new resets:                %llu\n", pDetails->numResets);
    fprintf(stdout, "    Number new programming errors:    %llu\n", pDetails->numProgrammingErrors);
    fprintf(stdout, "    Number new driver errors:         %llu\n", pDetails->numDriverErrors);
    fprintf(stdout, "    Number new compute errors:        %llu\n", pDetails->numComputeErrors);
    fprintf(stdout, "    Number new non-compute errors:    %llu\n", pDetails->numNonComputeErrors);
    fprintf(stdout, "    Number new cache errors:          %llu\n", pDetails->numCacheErrors);
    fprintf(stdout, "    Number new memory errors:         %llu\n", pDetails->numMemoryErrors);
    fprintf(stdout, "    Number new PCI errors:            %llu\n", pDetails->numPciErrors);
    fprintf(stdout, "    Number new switch errors:         %llu\n", pDetails->numSwitchErrors);
    fprintf(stdout, "    Number new display errors:        %llu\n", pDetails->numDisplayErrors);
}

void ShowRasErrors(xet_sysman_handle_t hSysmanDevice)
{
    xet_ras_properties_t props;
    if (xetSysmanRasGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "RAS supported: %s\n", props.supported ? "yes" : "no");
        fprintf(stdout, "RAS enabled: %s\n", props.enabled ? "yes" : "no");
        fprintf(stdout, "RAS repaired: %s\n", props.repaired ? "yes" : "no");
        if (props.supported && props.enabled)
        {
            uint64_t newErrors;
            xet_ras_details_t errorDetails;
            if (xetSysmanRasGetErrors(hSysmanDevice, XET_RAS_ERROR_TYPE_UNCORRECTABLE, 1, &newErrors, &errorDetails) == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "RAS new uncorrectable errors: %llu\n", newErrors);
                if (newErrors)
                {
                    PrintRasDetails(&errorDetails);
                }
            }
            if (xetSysmanRasGetErrors(hSysmanDevice, XET_RAS_ERROR_TYPE_CORRECTABLE, 1, &newErrors, &errorDetails) == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "RAS new correctable errors: %llu\n", newErrors);
                if (newErrors)
                {
                    PrintRasDetails(&errorDetails);
                }
            }
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

void ShowSwitchInfo(xet_sysman_handle_t hSysmanDevice, uint32_t SwitchIndex)
{
    xet_switch_properties_t swprops;
    if (xetSysmanSwitchGetProperties(hSysmanDevice, SwitchIndex, &swprops) == XE_RESULT_SUCCESS)
    {
        xet_switch_state_t swstate;
        if (xetSysmanSwitchGetState(hSysmanDevice, SwitchIndex, &swstate) == XE_RESULT_SUCCESS)
        {
            fprintf(stdout, "        #port:         %u\n", swprops.numPorts);
            if (swprops.onSubdevice)
            {
                fprintf(stdout, "        On sub-device: %s\n", swprops.subdeviceUuid.id);
            }
            fprintf(stdout, "        State:         %s\n", swstate.enabled ? "Enabled" : "Disabled");
            if (swstate.enabled)
            {
                fprintf(stdout, "        Ports:\n");
                for (uint32_t portIndex = 0; portIndex < swprops.numPorts; portIndex++)
                {
                    xet_switch_port_state_t portstate;
                    if (xetSysmanSwitchPortGetState(hSysmanDevice, SwitchIndex, portIndex, &portstate)
                        == XE_RESULT_SUCCESS)
                    {
                        if (portstate.isConnected)
                        {
                            fprintf(stdout,
                                "            %u: "
                                "connected to switch on device UUID %s, max rx/tx bandwidth %u/%u bytes/sec\n",
                                portIndex, portstate.remoteDeviceUuid.id,
                                portstate.rxSpeed.maxBandwidth, portstate.txSpeed.maxBandwidth);
                        }
                        else
                        {
                            fprintf(stdout, "            %u: not connected\n", portIndex);
                        }
                    }
                }
            }
        }
    }
}

void ShowSwitches(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t props;
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        if (props.numSwitches)
        {
            for (uint32_t switchIndex = 0; switchIndex < props.numSwitches; switchIndex++)
            {
                fprintf(stdout, "    Switch %u:\n", switchIndex);
                ShowSwitchInfo(hSysmanDevice, switchIndex);
            }
        }
    }
}

void FixFrequency(xet_sysman_handle_t hSysmanDevice, xet_freq_domain_t Domain, double FreqMHz)
{
    xet_freq_properties_t props;
    if (xetSysmanFrequencyGetProperties(hSysmanDevice, Domain, &props) == XE_RESULT_SUCCESS)
    {
        if (props.canControl)
        {
            xet_freq_limits_t limits;
            limits.min = FreqMHz;
            limits.max = FreqMHz;
            if (xetSysmanFrequencySetLimits(hSysmanDevice, Domain, &limits) != XE_RESULT_SUCCESS)
            {
                fprintf(stderr, "ERROR: Problem setting the frequency limits.\n");
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Can't control this frequency domain.\n");
        }
    }
}

void SetFanSpeed(xet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    xet_sysman_properties_t props;
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        if (props.numFans)
        {
            xet_fan_config_t config;
            config.mode = XET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = XET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < props.numFans; fanIndex++)
            {
                xet_fan_properties_t fanprops;
                if (xetSysmanFanGetProperties(hSysmanDevice, fanIndex, &fanprops) == XE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        xetSysmanFanSetConfig(hSysmanDevice, fanIndex, &config);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Can't control fan %u.\n", fanIndex);
                    }
                }
            }
        }
    }
}

void ShowFans(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t props;
    
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        if (props.numFans)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < props.numFans; fanIndex++)
            {
                xet_fan_state_t state;
                if (xetSysmanFanGetState(hSysmanDevice, fanIndex, XET_FAN_SPEED_UNITS_RPM, &state)
                    == XE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %u RPM\n", fanIndex, state.speed);
                }
            }
        }
    }
}

void ShowAveragePower(xet_sysman_handle_t hSysmanDevice, xet_power_energy_counter_t* pPrevEnergyCounter)
{
    xet_power_energy_counter_t newEnergyCounter;
    if (xetSysmanPowerGetEnergyCounter(hSysmanDevice, &newEnergyCounter) == XE_RESULT_SUCCESS)
    {
        uint64_t deltaTime = newEnergyCounter.timestamp - pPrevEnergyCounter->timestamp;
        if (deltaTime)
        {
            fprintf(stdout, "    Average power: %.3f W\n",
                ((double)(newEnergyCounter.energy - pPrevEnergyCounter->energy)) / ((double)deltaTime));
            *pPrevEnergyCounter = newEnergyCounter;
        }
    }
}

void ShowPowerLimits(xet_sysman_handle_t hSysmanDevice)
{
    xet_power_sustained_limit_t sustainedLimits;
    xet_power_burst_limit_t burstLimits;
    xet_power_peak_limit_t peakLimits;
    if (xetSysmanPowerGetLimits(hSysmanDevice, &sustainedLimits, &burstLimits, &peakLimits) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Power limits\n");
        if (sustainedLimits.enabled)
        {
            fprintf(stdout, "        Sustained: %.3f W %.3f sec\n",
                ((double)sustainedLimits.power) / 1000, ((double)sustainedLimits.interval) / 1000);
        }
        else
        {
            fprintf(stdout, "        Sustained: Disabled\n");
        }
        if (burstLimits.enabled)
        {
            fprintf(stdout, "        Burst:     %.3f\n", ((double)burstLimits.power) / 1000);
        }
        else
        {
            fprintf(stdout, "        Burst:     Disabled\n");
        }
        fprintf(stdout, "        Burst:     %.3f\n", ((double)peakLimits.power) / 1000);
    }
}

void ShowDeviceInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t props;
    xet_operating_mode_t mode;
    
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &props) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:    %s\n", props.uuid.id);
        fprintf(stdout, "    brand:   %s\n", props.brandName);
        fprintf(stdout, "    model:   %s\n", props.modelName);
        fprintf(stdout, "    serial#: %s\n", props.serialNumber);
        fprintf(stdout, "    board#:  %s\n", props.boardNumber);
    }
    if (xetSysmanDeviceGetOperatingMode(hSysmanDevice, &mode) == XE_RESULT_SUCCESS)
    {
        switch (mode)
        {
        case XET_OPERATING_MODE_EXCLUSIVE_COMPUTE_PROCESS:
            fprintf(stdout, "    mode:    exclusive compute process\n");
            break;
        default:
            fprintf(stdout, "    mode:    multiply process\n");
            break;
        }
    }
}

int gNumDevices = 0;    // Global

int ListDevice(xe_device_handle_t hDevice)
{
    int ret = 0;

    xet_sysman_handle_t hSysmanDevice;
    xe_result_t res = xetSysmanGet(hDevice, XET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
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
        uint32_t driversCount = 0;
        xeGetDrivers(&driversCount, nullptr);
        xe_driver_handle_t* allDrivers = (xe_driver_handle_t*)
            malloc(driversCount * sizeof(xe_driver_handle_t));
        xeGetDrivers(&driversCount, allDrivers);

        // Find the first GPU device group
        xe_driver_handle_t hDriver = nullptr;
        for(uint32_t i = 0; i < driversCount; ++i)
        {
            uint32_t deviceCount = 0;
            xeDriverGetDevices(allDrivers[i], &deviceCount, nullptr);

            xe_device_handle_t* allDevices = (xe_device_handle_t*)
                malloc(deviceCount * sizeof(xe_device_handle_t));
            xeDriverGetDevices(allDrivers[i], &deviceCount, allDevices);

            for(uint32_t d = 0; d < deviceCount; ++i)
            {
                xe_device_properties_t device_properties;
                xeDeviceGetProperties(allDevices[d], &device_properties);
                if(XE_DEVICE_TYPE_GPU == device_properties.type)
                {
                    if ((ret = ListDevice(allDevices[d])) != 0)
                    {
                        break;
                    }
                }
            }

            free(allDevices);
        }

        free(allDrivers);
    }

    if (gNumDevices == 0)
    {
        fprintf(stdout, "No managed devices found.\n");
    }

    return ret;
}
