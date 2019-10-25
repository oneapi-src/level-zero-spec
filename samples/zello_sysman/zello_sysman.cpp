/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "zello_sysman.h"

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "zet_api.h"

void PrintRasDetails(zet_ras_details_t* pDetails)
{
    fprintf(stdout, "        Number new resets:                %llu\n", (long long unsigned int)pDetails->numResets);
    fprintf(stdout, "        Number new programming errors:    %llu\n", (long long unsigned int)pDetails->numProgrammingErrors);
    fprintf(stdout, "        Number new driver errors:         %llu\n", (long long unsigned int)pDetails->numDriverErrors);
    fprintf(stdout, "        Number new compute errors:        %llu\n", (long long unsigned int)pDetails->numComputeErrors);
    fprintf(stdout, "        Number new non-compute errors:    %llu\n", (long long unsigned int)pDetails->numNonComputeErrors);
    fprintf(stdout, "        Number new cache errors:          %llu\n", (long long unsigned int)pDetails->numCacheErrors);
    fprintf(stdout, "        Number new memory errors:         %llu\n", (long long unsigned int)pDetails->numMemoryErrors);
    fprintf(stdout, "        Number new PCI errors:            %llu\n", (long long unsigned int)pDetails->numPciErrors);
    fprintf(stdout, "        Number new fabric errors:         %llu\n", (long long unsigned int)pDetails->numFabricErrors);
    fprintf(stdout, "        Number new display errors:        %llu\n", (long long unsigned int)pDetails->numDisplayErrors);
}

void ShowRasErrors(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRasErrorSets;
    if ((zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, NULL) == ZE_RESULT_SUCCESS) && numRasErrorSets)
    {
        zet_sysman_ras_handle_t* phRasErrorSets =
            (zet_sysman_ras_handle_t*)malloc(numRasErrorSets * sizeof(zet_sysman_ras_handle_t));
        if (zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t rasIndex = 0; rasIndex < numRasErrorSets; rasIndex++)
            {
                zet_ras_properties_t props;
                if (zetSysmanRasGetProperties(phRasErrorSets[rasIndex], &props) == ZE_RESULT_SUCCESS)
                {
                    const char* pErrorType;
                    switch (props.type)
                    {
                    case ZET_RAS_ERROR_TYPE_CORRECTABLE:
                        pErrorType = "Correctable";
                        break;
                    case ZET_RAS_ERROR_TYPE_UNCORRECTABLE:
                        pErrorType = "Uncorrectable";
                        break;
                    default:
                        pErrorType = "Unknown";
                        break;
                    }
                    fprintf(stdout, "RAS %s errors\n", pErrorType);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "    On sub-device: %u\n", props.subdeviceId);
                    }
                    fprintf(stdout, "    RAS supported: %s\n", props.supported ? "yes" : "no");
                    fprintf(stdout, "    RAS enabled: %s\n", props.enabled ? "yes" : "no");
                    if (props.supported && props.enabled)
                    {
                        uint64_t newErrors;
                        zet_ras_details_t errorDetails;
                        if (zetSysmanRasGetErrors(phRasErrorSets[rasIndex], 1, &newErrors, &errorDetails)
                            == ZE_RESULT_SUCCESS)
                        {
                            fprintf(stdout, "    Number new errors: %llu\n", (long long unsigned int)newErrors);
                            if (newErrors)
                            {
                                PrintRasDetails(&errorDetails);
                            }
                        }
                    }
                }
            }
        }
        free(phRasErrorSets);
    }
}

void ListDiagnosticTests(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numTestSuites;
    if ((zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, NULL) == ZE_RESULT_SUCCESS) && numTestSuites)
    {
        zet_sysman_diag_handle_t* phTestSuites =
            (zet_sysman_diag_handle_t*)malloc(numTestSuites * sizeof(zet_sysman_diag_handle_t));
        if (zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, phTestSuites) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t suiteIndex = 0; suiteIndex < numTestSuites; suiteIndex++)
            {
                zet_diag_properties_t suiteProps;
                if (zetSysmanDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "Diagnostic test suite %s:\n", suiteProps.name);
                    if (suiteProps.numTests)
                    {
                        for (uint32_t i = 0; i < suiteProps.numTests; i++)
                        {
                            const zet_diag_test_t* pTest = &suiteProps.pTests[i];
                            fprintf(stdout, "    Test %u: %s\n", pTest->index, pTest->name);
                        }
                    }
                    else
                    {
                        fprintf(stdout, "    Cannot run subset of tests.\n");
                    }
                }
            }
        }
        free(phTestSuites);
    }
}

void ResetDevice(zet_sysman_handle_t hSysmanDevice)
{
    if (zetSysmanDeviceReset(hSysmanDevice))
    {
        fprintf(stdout, "Device reset initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem resetting the device.\n");
    }
}

void ShowFabricPortInfo(zet_sysman_fabric_port_handle_t hPort)
{
    zet_fabric_port_properties_t props;
    if (zetSysmanFabricPortGetProperties(hPort, &props) == ZE_RESULT_SUCCESS)
    {
        zet_fabric_port_state_t state;
        if (zetSysmanFabricPortGetState(hPort, &state) == ZE_RESULT_SUCCESS)
        {
            zet_fabric_link_type_t link;
            if (zetSysmanFabricPortGetLinkType(hPort, false, &link) == ZE_RESULT_SUCCESS)
            {
                zet_fabric_port_config_t config;
                if (zetSysmanFabricPortGetConfig(hPort, &config) == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout,
                        "        Model:                 %s\n", props.model);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout,
                            "        On sub-device:         %u\n", props.subdeviceId);
                    }
                    if (config.enabled)
                    {
                        const char* status;
                        fprintf(stdout,
                            "        Config:                UP\n");
                        switch (state.status)
                        {
                        case ZET_FABRIC_PORT_STATUS_GREEN:
                            status = "GREEN - The port is up and operating as expected";
                            break;
                        case ZET_FABRIC_PORT_STATUS_YELLOW:
                            status = "YELLOW - The port is up but has quality and/or bandwidth degradation";
                            break;
                        case ZET_FABRIC_PORT_STATUS_RED:
                            status = "RED - Port connection instabilities";
                            break;
                        case ZET_FABRIC_PORT_STATUS_BLACK:
                            status = "BLACK - The port is configured down";
                            break;
                        default:
                            status = "UNKNOWN";
                            break;
                        }
                        fprintf(stdout,
                            "        Status:                %s\n", status);
                        fprintf(stdout,
                            "        Link type:             %s\n", link.desc);
                        fprintf(stdout,
                            "        Max speed (rx/tx):     %llu/%llu bytes/sec\n",
                            (long long unsigned int)props.maxRxSpeed.maxBandwidth,
                            (long long unsigned int)props.maxTxSpeed.maxBandwidth);
                        fprintf(stdout,
                            "        Current speed (rx/tx): %llu/%llu bytes/sec\n",
                            (long long unsigned int)state.rxSpeed.maxBandwidth,
                            (long long unsigned int)state.txSpeed.maxBandwidth);
                    }
                    else
                    {
                        fprintf(stdout,
                            "        Config:                DOWN\n");
                    }
                }
            }
        }
    }
}

void ShowFabricPorts(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPorts;
    if ((zetSysmanFabricPortGet(hSysmanDevice, &numPorts, NULL) == ZE_RESULT_SUCCESS) && numPorts)
    {
        zet_sysman_fabric_port_handle_t* phPorts =
            (zet_sysman_fabric_port_handle_t*)malloc(numPorts * sizeof(zet_sysman_fabric_port_handle_t));
        if (zetSysmanFabricPortGet(hSysmanDevice, &numPorts, phPorts) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numPorts; index++)
            {
                fprintf(stdout, "    Port %u:\n", index);
                ShowFabricPortInfo(phPorts[index]);
            }
        }
        free(phPorts);
    }
}

void ShowOcCapabilities(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_DOMAIN_GPU)
                    {
                        zet_oc_capabilities_t oc_caps;
                        if (zetSysmanFrequencyGetOcCapabilities(pFreqHandles[index], &oc_caps) == ZE_RESULT_SUCCESS)
                        {
                            if (oc_caps.FrequencyOcSupported)
                            {
                                fprintf(stdout, "    Over clock Capabilities\n");
                                fprintf(stdout, "    Max Oc Frequency: %.3f\n", oc_caps.MaxOcFrequencyLimit);
                                fprintf(stdout, "    Max Factory Default Frequency: %.3f\n", oc_caps.MaxFactoryDefaultFrequency);
                                fprintf(stdout, "    Max Factory Default Voltage: %.3f\n", oc_caps.MaxFactoryDefaultVoltage);
                                fprintf(stdout, "    Is Voltage Override Supported: %s\n", oc_caps.VoltageOverrideSupported ? "yes" : "no");
                                fprintf(stdout, "    Is High Voltage Capable: %s\n", oc_caps.HighVoltModeCapable ? "yes" : "no");
                                fprintf(stdout, "    Is High Voltage Enabled: %s\n", oc_caps.HighVoltModeEnabled ? "yes" : "no");
                                fprintf(stdout, "    Is TjMax Supported: %s\n", oc_caps.TjMaxSupported ? "yes" : "no");
                                fprintf(stdout, "    Is IccMax Supported: %s\n", oc_caps.IccMaxSupported ? "yes" : "no");

                                if (oc_caps.IccMaxSupported)
                                {
                                    zet_oc_icc_max_t iccmax;
                                    if (zetSysmanFrequencyGetOcIccMax(pFreqHandles[index], &iccmax) == ZE_RESULT_SUCCESS) 
                                    {
                                        fprintf(stdout, "    Icc Max: %.3f\n", iccmax.IccMax);
                                    }
                                    else 
                                    {
                                        zet_oc_error_type_t oc_error;
                                        if (zetSysmanFrequencyGetLastOcError(pFreqHandles[index], &oc_error) == ZE_RESULT_SUCCESS)
                                        {
                                            fprintf(stderr, "ERROR: Failure to get Icc Max with error %u on domain with index %u.\n", oc_error, index);
                                        }
                                        else
                                        {
                                            fprintf(stderr, "ERROR: Can't get Oc Error and failure to overclock domain with index %u.\n", index);
                                        }
                                    }
                                }

                                if (oc_caps.TjMaxSupported)
                                {
                                    zet_oc_tj_max_t tjmax;
                                    if (zetSysmanFrequencyGetOcTjMax(pFreqHandles[index], &tjmax) == ZE_RESULT_SUCCESS)
                                    {
                                        fprintf(stdout, "    TjMax: %.3f\n", tjmax.TjMax);
                                    }
                                    else
                                    {
                                        zet_oc_error_type_t oc_error;
                                        if (zetSysmanFrequencyGetLastOcError(pFreqHandles[index], &oc_error) == ZE_RESULT_SUCCESS)
                                        {
                                            fprintf(stderr, "ERROR: Failure to get TjMax with error %u on domain with index %u.\n", oc_error, index);
                                        }
                                        else
                                        {
                                            fprintf(stderr, "ERROR: Can't get Oc Error and failure to overclock domain with index %u.\n", index);
                                        }
                                    }
                                }
                                                 
                                // Set new max Oc frequency only if is not above the maximum Oc frequency limit.
                                double CurrentMaxFrequencyMhz = oc_caps.MaxFactoryDefaultFrequency;
                                CurrentMaxFrequencyMhz *= 1.1;
                                if (CurrentMaxFrequencyMhz <= oc_caps.MaxOcFrequencyLimit)
                                {
                                    zet_oc_configuration_t config;
                                    config.OcFrequency = CurrentMaxFrequencyMhz;
                                    config.TargetMode = zet_oc_mode_t::ZET_OVERCLOCKING_INTERPOLATIVE_MODE;
                                    config.TargetVoltage = oc_caps.MaxFactoryDefaultVoltage;
                                    config.VoltageOffset = 0.0;

                                    if(zetSysmanFrequencySetOcConfig(pFreqHandles[index], &config) == ZE_RESULT_SUCCESS)
                                        {
                                            fprintf(stdout, "    Oc Frequency successfully set to: %.3f Mhz\n", CurrentMaxFrequencyMhz);
                                        }
                                    else
                                    {
                                        zet_oc_error_type_t oc_error;
                                        if (zetSysmanFrequencyGetLastOcError(pFreqHandles[index], &oc_error) == ZE_RESULT_SUCCESS)
                                        {
                                            fprintf(stderr, "ERROR: Failure to overclock with error %u on domain with index %u.\n", oc_error, index);
                                        }
                                        else
                                        {
                                            fprintf(stderr, "ERROR: Can't get Oc Error and failure to overclock domain with index %u.\n", index);
                                        }
                                    }
                                }

                                {
                                    // Show current configuration
                                    zet_oc_configuration_t config;
                                    if (zetSysmanFrequencyGetOcConfig(pFreqHandles[index], &config) == ZE_RESULT_SUCCESS)
                                    {
                                        fprintf(stdout, "    Current Oc Frequency: %.3f Mhz\n", config.OcFrequency);                                        
                                        fprintf(stdout, "    Current Voltage: %.3f Volts\n", config.TargetVoltage);
                                        fprintf(stdout, "    Current Voltage Offset: %.3f volts\n", config.VoltageOffset);
                                        fprintf(stdout, "    Current Target Mode: %s\n", config.TargetMode == zet_oc_mode_t::ZET_OVERCLOCKING_INTERPOLATIVE_MODE ?
                                                                                        "interpolative mode" : "override mode");
                                    }
                                    else
                                    {
                                        zet_oc_error_type_t oc_error;
                                        if (zetSysmanFrequencyGetLastOcError(pFreqHandles[index], &oc_error) == ZE_RESULT_SUCCESS)
                                        {
                                            fprintf(stderr, "ERROR: Failure to overclock with error %u on domain with index %u.\n", oc_error, index);
                                        }
                                        else
                                        {
                                            fprintf(stderr, "ERROR: Can't get Oc Error and failure to overclock domain with index %u.\n", index);
                                        }
                                    }
                                }

                            }
                            else
                            {
                                fprintf(stderr, "ERROR: Overclocking is not supported on the current domain with index %u.\n", index);
                            }
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }    
}

void FixGpuFrequency(zet_sysman_handle_t hSysmanDevice, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_DOMAIN_GPU)
                    {
                        if (props.canControl)
                        {
                            zet_freq_range_t range;
                            range.min = FreqMHz;
                            range.max = FreqMHz;
                            if (zetSysmanFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
                            {
                                fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                            }
                        }
                        else
                        {
                            fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                        }
                    }
                }              
            }
        }
        free(pFreqHandles);
    }
}

void FixSubdeviceGpuFrequency(zet_sysman_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_DOMAIN_GPU)
                    {
                        // Only control the GPU frequency domain for a specific sub-device
                        if (props.onSubdevice && (props.subdeviceId == subdeviceId))
                        {
                            if (props.canControl)
                            {
                                zet_freq_range_t range;
                                range.min = FreqMHz;
                                range.max = FreqMHz;
                                if (zetSysmanFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
                                {
                                    fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                                }
                            }
                            else
                            {
                                fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                            }
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }
}

void SetFanSpeed(zet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans;
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_fan_handle_t* phFans =
            (zet_sysman_fan_handle_t*)malloc(numFans * sizeof(zet_sysman_fan_handle_t));
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            zet_fan_config_t config;
            config.mode = ZET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = ZET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                zet_fan_properties_t fanprops;
                if (zetSysmanFanGetProperties(phFans[fanIndex], &fanprops) == ZE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        zetSysmanFanSetConfig(phFans[fanIndex], &config);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Can't control fan %u.\n", fanIndex);
                    }
                }
            }
        }
        free(phFans);
    }
}

void ShowFans(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_fan_handle_t* phFans =
            (zet_sysman_fan_handle_t*)malloc(numFans * sizeof(zet_sysman_fan_handle_t));
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                zet_fan_state_t state;
                if (zetSysmanFanGetState(phFans[fanIndex], ZET_FAN_SPEED_UNITS_RPM, &state)
                    == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %u RPM\n", fanIndex, state.speed);
                }
            }
        }
        free(phFans);
    }
}

void ShowAveragePower(zet_sysman_pwr_handle_t hPower, zet_power_energy_counter_t* pPrevEnergyCounter)
{
    zet_power_energy_counter_t newEnergyCounter;
    if (zetSysmanPowerGetEnergyCounter(hPower, &newEnergyCounter) == ZE_RESULT_SUCCESS)
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

// Forward declarations
void ShowPowerLimits(zet_sysman_pwr_handle_t hPower);
void ShowEnergyThreshold(zet_sysman_pwr_handle_t hPower);

void ShowPowerDomains(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPowerDomains;
    if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_pwr_handle_t* phPower =
            (zet_sysman_pwr_handle_t*)malloc(numPowerDomains * sizeof(zet_sysman_pwr_handle_t));
        if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, phPower) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t pwrIndex = 0; pwrIndex < numPowerDomains; pwrIndex++)
            {
                zet_power_properties_t props;
                if (zetSysmanPowerGetProperties(phPower[pwrIndex], &props) == ZE_RESULT_SUCCESS)
                {
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "Sub-device %u power:\n", props.subdeviceId);
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                    else
                    {
                        fprintf(stdout, "Total package power:\n");
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                }

                ShowEnergyThreshold(phPower[pwrIndex]);
            }
        }
        free(phPower);
    }
}

void ShowPowerLimits(zet_sysman_pwr_handle_t hPower)
{
    zet_power_sustained_limit_t sustainedLimits;
    zet_power_burst_limit_t burstLimits;
    zet_power_peak_limit_t peakLimits;
    if (zetSysmanPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == ZE_RESULT_SUCCESS)
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
        fprintf(stdout, "        Peak AC:     %.3f\n", ((double)peakLimits.powerAC) / 1000);
        fprintf(stdout, "        Peak DC:     %.3f\n", ((double)peakLimits.powerDC) / 1000);
    }
}

void ShowEnergyThreshold(zet_sysman_pwr_handle_t hPower)
{
    zet_power_energy_threshold_t energyThreshold;
    if (zetSysmanPowerGetEnergyThreshold(hPower, &energyThreshold) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Energy Threshold: %d\n", energyThreshold.energy);
    }

}

void ShowDeviceInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_sysman_properties_t devProps;
    ze_bool_t repaired;
    if (zetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    is discrete:    %s\n", devProps.deviceType == zet_device_type_t::ZET_DEVICE_TYPE_DISCRETE ? "yes" : "no");
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (zetSysmanDeviceWasRepaired(hSysmanDevice, &repaired) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", repaired ? "yes" : "no");
    }
}

void DisableSchedulerWatchdog(zet_sysman_handle_t hSysmanDevice)
{
    ze_result_t res;
    zet_sched_mode_t currentMode;
    res = zetSysmanSchedulerGetCurrentMode(hSysmanDevice, &currentMode);
    if (res == ZE_RESULT_SUCCESS)
    {
        ze_bool_t requireReboot;
        zet_sched_timeout_properties_t props;
        props.watchdogTimeout = ZET_SCHED_WATCHDOG_DISABLE;
        res = zetSysmanSchedulerSetTimeoutMode(hSysmanDevice, &props, &requireReboot);
        if (res == ZE_RESULT_SUCCESS)
        {
            if (requireReboot)
            {
                fprintf(stderr, "WARNING: Reboot required to complete desired configuration.\n");
            }
            else
            {
                fprintf(stdout, "Schedule mode changed successfully.\n");
            }
        }
        else if(res == ZE_RESULT_ERROR_UNSUPPORTED)
        {
            fprintf(stderr, "ERROR: The timeout scheduler mode is not supported on this device.\n");
        }
        else if(res == ZE_RESULT_ERROR_INSUFFICENT_PERMISSIONS)
        {
            fprintf(stderr, "ERROR: Don't have permissions to change the scheduler mode.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Problem calling the API to change the scheduler mode.\n");
        }
    }
    else if(res == ZE_RESULT_ERROR_UNSUPPORTED)
    {
        fprintf(stderr, "ERROR: Scheduler modes are not supported on this device.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem calling the API.\n");
    }
}

void ShowPciInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_pci_properties_t pciProps;
    if (zetSysmanPciGetProperties(hSysmanDevice, &pciProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    PCI address:        %04u:%02u:%02u.%u\n", pciProps.address.domain, pciProps.address.bus, pciProps.address.device, pciProps.address.function);
    }
}

int gNumDevices = 0;    // Global

int ListDevice(ze_device_handle_t hDevice)
{
    int ret = 0;

    zet_sysman_handle_t hSysmanDevice;
    ze_result_t res = zetSysmanGet(hDevice, ZET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
    if (res == ZE_RESULT_SUCCESS)
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
    if ( (zeInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) ||
         (zetInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t driversCount = 0;
        zeDriverGet(&driversCount, nullptr);
        ze_driver_handle_t* allDrivers = (ze_driver_handle_t*)
            malloc(driversCount * sizeof(ze_driver_handle_t));
        zeDriverGet(&driversCount, allDrivers);

        // Find the first GPU device group
        ze_driver_handle_t hDriver = nullptr;
        for(uint32_t i = 0; i < driversCount; ++i)
        {
            uint32_t deviceCount = 0;
            zeDeviceGet(allDrivers[i], &deviceCount, nullptr);

            ze_device_handle_t* allDevices = (ze_device_handle_t*)
                malloc(deviceCount * sizeof(ze_device_handle_t));
            zeDeviceGet(allDrivers[i], &deviceCount, allDevices);

            for(uint32_t d = 0; d < deviceCount; ++i)
            {
                ze_device_properties_t device_properties;
                zeDeviceGetProperties(allDevices[d], &device_properties);
                if(ZE_DEVICE_TYPE_GPU == device_properties.type)
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
