#include "device.h"

#include "builtin_functions_lib.h"
#include "cmdlist.h"
#include "cmdqueue.h"
#include "event.h"
#include "memory_manager.h"
#include "mocs_mapper.h"
#include "module.h"
#include "image.h"
#include "runtime/device/device.h"
#include "runtime/helpers/hw_helper.h"
#include "runtime/helpers/string.h"
#include "runtime/kernel/grf_config.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include "runtime/command_queue/command_queue.h"
#include "runtime/execution_environment/execution_environment.h"
#include "runtime/mem_obj/mem_obj.h"
#include "runtime/helpers/validators.h"
#include "runtime/program/program.h"

namespace L0 {

class ProgramRTHelper : public NEO::Program {
    public:
        uint8_t* getIrBinary() { return reinterpret_cast<uint8_t*>(irBinary); }
        size_t getIrBinarySize() { return irBinarySize; }
};

struct DeviceImp : public Device {
    xe_result_t canAccessPeer(xe_device_handle_t hPeerDevice,
                              xe_bool_t *value) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t copyCommandList(xe_command_list_handle_t hCommandList,
                                xe_command_list_handle_t *phCommandList) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    //xe_result_t createCommandGraph(const xe_command_graph_desc_t *desc,
    //                               xe_command_graph_handle_t *phCommandGraph) override {
    //    return XE_RESULT_ERROR_UNSUPPORTED;
    //}

    xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                  xe_command_list_handle_t *commandList) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;
        *commandList = CommandList::create(productFamily, this);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                   xe_command_queue_handle_t *commandQueue) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;

        auto executionEnvironment = deviceRT->getExecutionEnvironment();
        auto csrRT = executionEnvironment->commandStreamReceivers[0][0].get();

        *commandQueue = CommandQueue::create(productFamily, this, csrRT);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createEventPool(const xe_event_pool_desc_t *desc,
                            xe_event_pool_handle_t *eventPool) override {
        *eventPool = EventPool::create(this, desc);
        return XE_RESULT_SUCCESS;
    }

    xe_result_t createImage(const xe_image_desc_t *desc,
                            xe_image_handle_t *phImage) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;
        *phImage = Image::create(productFamily, this, desc);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createModule(const xe_module_desc_t *desc,
                             xe_module_handle_t *module,
                             xe_module_build_log_handle_t *buildLog) override {
        ModuleBuildLog *moduleBuildLog = nullptr;

        if (buildLog) {
            moduleBuildLog = ModuleBuildLog::create();
            *buildLog = moduleBuildLog->toHandle();
        }
        *module = Module::create(this, desc, deviceRT, moduleBuildLog);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createSampler(const xe_sampler_desc_t *pDesc,
                              xe_sampler_handle_t *phSampler) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t evictImage(xe_image_handle_t hImage) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t evictMemory(void *ptr,
                            size_t size) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getApiVersion(xe_api_version_t *version) override {
        assert(version != nullptr);
        *version = XE_API_VERSION_1_0;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getComputeProperties(xe_device_compute_properties_t *pComputeProperties) override {
        assert(pComputeProperties != nullptr);
        assert(pComputeProperties->version == XE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT);
        const auto &deviceInfo = this->deviceRT->getDeviceInfo();

        pComputeProperties->maxThreadsPerGroup = static_cast<uint32_t>(deviceInfo.maxWorkGroupSize); // threads per group or items per group?! Clarify naming vs maxGroupSizeX/Y/Z
        pComputeProperties->maxGroupSizeX = pComputeProperties->maxThreadsPerGroup;                  // Note : it doesn't mean that it can be max x max x max
        pComputeProperties->maxGroupSizeY = pComputeProperties->maxThreadsPerGroup;                  //        rather max x 1 x 1
        pComputeProperties->maxGroupSizeZ = pComputeProperties->maxThreadsPerGroup;                  //
        pComputeProperties->maxGroupCountX = static_cast<uint32_t>(deviceInfo.maxWorkItemSizes[0]);  // assuming 1 x y z  // need clarification on the intent
        pComputeProperties->maxGroupCountY = static_cast<uint32_t>(deviceInfo.maxWorkItemSizes[1]);  // assuming x x 1 z
        pComputeProperties->maxGroupCountZ = static_cast<uint32_t>(deviceInfo.maxWorkItemSizes[2]);  // assuming x x y 1
        pComputeProperties->maxSharedLocalMemory = static_cast<uint32_t>(deviceInfo.localMemSize);
        pComputeProperties->maxGroupRegisters = GrfConfig::DefaultGrfNumber; // registers per group or subgroup?! Need clarification
        pComputeProperties->numSubGroupSizes = sizeof(deviceInfo.maxSubGroups) / sizeof(deviceInfo.maxSubGroups[0]);
        for (uint32_t i = 0; i < pComputeProperties->numSubGroupSizes; ++i) {
            pComputeProperties->subGroupSizes[i] = static_cast<uint32_t>(deviceInfo.maxSubGroups[i]);
        }

        return XE_RESULT_SUCCESS;
    }

    xe_result_t getP2PProperties(xe_device_handle_t hPeerDevice,
                                 xe_device_p2p_properties_t *pP2PProperties) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getMemoryProperties(xe_device_memory_properties_t *pMemProperties) override {
        assert(pMemProperties != nullptr);
        assert(pMemProperties->version == XE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT);
        const auto &deviceInfo = this->deviceRT->getDeviceInfo();
        const auto &hardwareInfo = this->deviceRT->getHardwareInfo();
        auto &hwHelper = NEO::HwHelper::get(hardwareInfo.pPlatform->eRenderCoreFamily);
        auto enableLocalMemory = hwHelper.getEnableLocalMemory(hardwareInfo);

        pMemProperties->unifiedMemory = true;                                                // need clarification - "Host and device share same physical memory."
                                                                                             //                      i.e. all physical memory?
        pMemProperties->onDemandPageFaults = false;                                          // TODO : Add support
        pMemProperties->maxImageDims1D = static_cast<uint32_t>(deviceInfo.image2DMaxWidth);  //
        pMemProperties->maxImageDims2D = static_cast<uint32_t>(deviceInfo.image2DMaxHeight); // need clarification : assumes max is square
        pMemProperties->maxImageDims3D = static_cast<uint32_t>(deviceInfo.image3DMaxDepth);  // need clarification : assumes max is a cube
        pMemProperties->maxImageArraySlices = static_cast<uint32_t>(deviceInfo.imageMaxArraySize);
        // Need clarification on XE_MEMORY_CONCURRENT_ACCESS and XE_MEMORY_CONCURRENT_ATOMIC_ACCESS
        pMemProperties->hostAllocCapabilities = xe_memory_access_capabilities_t{}; // system level SVM? need clarification
        pMemProperties->deviceAllocCapabilities = static_cast<xe_memory_access_capabilities_t>(XE_MEMORY_ACCESS | XE_MEMORY_ATOMIC_ACCESS);
        pMemProperties->sharedAllocCapabilities = XE_MEMORY_ACCESS;
        if (false == enableLocalMemory) {
            pMemProperties->sharedAllocCapabilities = static_cast<xe_memory_access_capabilities_t>(XE_MEMORY_ACCESS | XE_MEMORY_ATOMIC_ACCESS);
        }
        pMemProperties->sharedCrossDeviceAllocCapabilities = xe_memory_access_capabilities_t{};  // need clarification
        pMemProperties->sharedSystemDeviceAllocCapabilities = xe_memory_access_capabilities_t{}; // need clarification
        pMemProperties->intermediateCacheSize = 0;                                               // TODO : does old L1$ count, or only PVC+? need clarification
        pMemProperties->intermediateCacheControl = false;
        pMemProperties->lastLevelCacheSize = static_cast<uint32_t>(deviceInfo.globalMemCacheSize);
        pMemProperties->lastLevelCacheSizeControl = true; // TODO : Not true for ATS+
                                                          // Need clarification : No stuff like cacheline size or (preferred) memory alignments
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getProperties(xe_device_properties_t *pDeviceProperties) override {
        assert(pDeviceProperties != nullptr);
        assert(pDeviceProperties->version == XE_DEVICE_PROPERTIES_VERSION_CURRENT);
        const auto &deviceInfo = this->deviceRT->getDeviceInfo();
        const auto &hardwareInfo = this->deviceRT->getHardwareInfo();
        auto &hwHelper = NEO::HwHelper::get(hardwareInfo.pPlatform->eRenderCoreFamily);
        auto enableLocalMemory = hwHelper.getEnableLocalMemory(hardwareInfo);

        memcpy_s(pDeviceProperties->name, sizeof(pDeviceProperties->name),
                 deviceInfo.name, strlen(deviceInfo.name) + 1);
        pDeviceProperties->coreClockRate =
                deviceInfo.maxClockFrequency;
        pDeviceProperties->vendorId =
                deviceInfo.vendorId;
        pDeviceProperties->deviceId =
                this->deviceRT->getDeviceIndex(); ///< [out] device id from PCI configuration
        pDeviceProperties->subdeviceId =
                isSubdevice ? this->deviceRT->getDeviceIndex() : 0;
        pDeviceProperties->isSubdevice =
                isSubdevice;
        pDeviceProperties->numSubDevices =
                isSubdevice ? 0 : deviceInfo.partitionMaxSubDevices;
        pDeviceProperties->coreClockRate =
                deviceInfo.maxClockFrequency;
        //pDeviceProperties->memClockRate; ///< [out] Clock rate for device global memory
        //pDeviceProperties->memGlobalBusWidth; ///< [out] Bus width between core and memory.
        pDeviceProperties->totalLocalMemSize =
                enableLocalMemory ?
                        NEO::DebugManager.flags.HBMSizePerTileInGigabytes.get()
                                * MemoryConstants::gigaByte : 0;
        pDeviceProperties->numAsyncComputeEngines =
                static_cast<uint32_t>(hwHelper.getGpgpuEngineInstances().size());
        pDeviceProperties->numAsyncCopyEngines = 1; //  hwHelper.getCopyEngineInstances().size(); // NEO refactor
        pDeviceProperties->maxCommandQueuePriority = 0; // map to cl_khr_priority_hints ?
        pDeviceProperties->numThreadsPerEU =
                deviceInfo.numThreadsPerEU;
        pDeviceProperties->numEUsPerSubslice =
                hardwareInfo.pSysInfo->MaxEuPerSubSlice * 2; // need clarification - does this make sense pre GEN11?
        pDeviceProperties->numSubslicesPerSlice =
                hardwareInfo.pSysInfo->MaxDualSubSlicesSupported
                        / hardwareInfo.pSysInfo->MaxSlicesSupported;
        pDeviceProperties->numSlicesPerTile =
                hardwareInfo.pSysInfo->MaxSlicesSupported;
        //pDeviceProperties->numTiles; ///< [out] Number of tiles for this device. TODO : Add support
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getSubDevice(uint32_t ordinal,
                             xe_device_handle_t *phSubDevice) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t makeImageResident(xe_image_handle_t hImage) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t makeMemoryResident(void *ptr,
                                   size_t size) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t setIntermediateCacheConfig(xe_cache_config_t CacheConfig) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t setLastLevelCacheConfig(xe_cache_config_t CacheConfig) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getImageProperties(const xe_image_desc_t* desc,
            xe_image_properties_t* pImageProperties) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    void *getExecEnvironment() override {
        return execEnvironment;
    }

    PtrRef<BuiltinFunctionsLib> getBuiltinFunctionsLib() override {
        return builtins.weakRef();
    }

    PtrRef<MOCSMapper> getMOCSMapper() override {
        return mocsMapper.weakRef();
    }

    NEO::HwHelper &getHwHelper() override {
        const auto &hardwareInfo = deviceRT->getHardwareInfo();
        return NEO::HwHelper::get(hardwareInfo.pPlatform->eRenderCoreFamily);
    }

    uint32_t getMaxNumHwThreads() const override {
        return maxNumHwThreads;
    }

    xe_result_t registerCLMemory(cl_context context, cl_mem mem, void** ptr) override {
        NEO::MemObj *memObjRT = static_cast<NEO::MemObj *>(mem);
        NEO::GraphicsAllocation *graphicsAllocationRT = memObjRT->getGraphicsAllocation();
        assert(graphicsAllocationRT != nullptr);

        auto allocation = new GraphicsAllocation(graphicsAllocationRT);
        allocation->setAllocatedFromCL(true);

        globalMemoryManager->registerCLMemory(allocation);

        *ptr = allocation->getHostAddress();

        return XE_RESULT_SUCCESS;
    }

    xe_result_t registerCLProgram(cl_context context, cl_program program,
            xe_module_handle_t* phModule) override {
        NEO::Program *programRT = static_cast<NEO::Program *>(program);

        if (programRT->getIsSpirV()) {
            uint8_t* spirvData = (reinterpret_cast<ProgramRTHelper*>(programRT))->getIrBinary();
            size_t spirvSize = (reinterpret_cast<ProgramRTHelper*>(programRT))->getIrBinarySize();

            xe_module_desc_t module_desc;
            module_desc.version = XE_MODULE_DESC_VERSION_CURRENT;
            module_desc.format = XE_MODULE_FORMAT_IL_SPIRV;
            module_desc.inputSize = spirvSize;
            module_desc.pInputModule = spirvData;
            module_desc.pBuildFlags = nullptr;

            return createModule(&module_desc, phModule, nullptr);
        } else {
            return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
    }

    xe_result_t registerCLCommandQueue(cl_context context,
            cl_command_queue command_queue,
            xe_command_queue_handle_t* phCommandQueue) override {

        NEO::CommandQueue *commandQueueRT = static_cast<NEO::CommandQueue *>(command_queue);

        *phCommandQueue =
                CommandQueue::create(commandQueueRT->getDevice().getHardwareInfo()
                        .pPlatform->eProductFamily, this,
                        reinterpret_cast<void *>(&commandQueueRT->getCommandStreamReceiver()));

        return XE_RESULT_SUCCESS;
    }

    NEO::Device *deviceRT = nullptr;
    bool isSubdevice = false;
    void *execEnvironment = nullptr;
    PtrOwn<BuiltinFunctionsLib> builtins = nullptr;
    PtrOwn<MOCSMapper> mocsMapper = nullptr;
    uint32_t maxNumHwThreads = 0;
};

// TODO: Refactor in NEO - remove dependency on template parameter
static uint32_t getMaxThreadsForVfe(const NEO::HardwareInfo &hwInfo) {
    uint32_t threadsPerEU = (hwInfo.pSysInfo->ThreadCount / hwInfo.pSysInfo->EUCount) + hwInfo.capabilityTable.extraQuantityThreadsPerEU;
    return hwInfo.pSysInfo->EUCount * threadsPerEU;
}

Device *Device::create(void *ptr) {
    auto device = new DeviceImp;

    auto deviceRT = static_cast<NEO::Device *>(ptr);
    device->deviceRT = deviceRT;

    device->execEnvironment = (void *)deviceRT->getExecutionEnvironment();
    device->builtins =
            BuiltinFunctionsLib::create(PtrRef<Device>(device),
                    PtrRef<void>(deviceRT->getExecutionEnvironment()->getBuiltIns()));
    device->mocsMapper.rebind(new MOCSMapper(bindPtrRef(deviceRT->getGmmHelper())));
    device->maxNumHwThreads = getMaxThreadsForVfe(deviceRT->getHardwareInfo());

    return device;
}

xe_result_t deviceGetP2PProperties(uint32_t srcOrdinal,
                                   uint32_t dstOrdinal,
                                   xe_device_p2p_properties_t *pP2PProperties) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
