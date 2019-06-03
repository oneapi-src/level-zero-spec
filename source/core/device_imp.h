#include "device.h"

namespace L0 {

struct DeviceImp : public Device {
    xe_result_t canAccessPeer(xe_device_handle_t hPeerDevice, xe_bool_t *value) override;
    xe_result_t copyCommandList(xe_command_list_handle_t hCommandList,
                                xe_command_list_handle_t *phCommandList) override;
    xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                  xe_command_list_handle_t *commandList) override;
    xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                   xe_command_queue_handle_t *commandQueue) override;
    xe_result_t createEventPool(const xe_event_pool_desc_t *desc,
                                xe_event_pool_handle_t *eventPool) override;
    xe_result_t createImage(const xe_image_desc_t *desc, xe_image_handle_t *phImage) override;
    xe_result_t createModule(const xe_module_desc_t *desc, xe_module_handle_t *module,
                             xe_module_build_log_handle_t *buildLog) override;
    xe_result_t createSampler(const xe_sampler_desc_t *pDesc,
                              xe_sampler_handle_t *phSampler) override;
    xe_result_t evictImage(xe_image_handle_t hImage) override;
    xe_result_t evictMemory(void *ptr, size_t size) override;
    xe_result_t getApiVersion(xe_api_version_t *version) override;
    xe_result_t getComputeProperties(xe_device_compute_properties_t *pComputeProperties) override;
    xe_result_t getP2PProperties(xe_device_handle_t hPeerDevice,
                                 xe_device_p2p_properties_t *pP2PProperties) override;
    xe_result_t getMemoryProperties(xe_device_memory_properties_t *pMemProperties) override;
    xe_result_t getProperties(xe_device_properties_t *pDeviceProperties) override;
    xe_result_t getSubDevice(uint32_t ordinal, xe_device_handle_t *phSubDevice) override;
    xe_result_t makeImageResident(xe_image_handle_t hImage) override;
    xe_result_t makeMemoryResident(void *ptr, size_t size) override;
    xe_result_t setIntermediateCacheConfig(xe_cache_config_t CacheConfig) override;
    xe_result_t setLastLevelCacheConfig(xe_cache_config_t CacheConfig) override;
    xe_result_t getImageProperties(const xe_image_desc_t *desc,
                                   xe_image_properties_t *pImageProperties) override;
    xe_result_t systemBarrier() override;
    void *getExecEnvironment() override;
    PtrRef<BuiltinFunctionsLib> getBuiltinFunctionsLib() override;
    PtrRef<MOCSMapper> getMOCSMapper() override;
    NEO::HwHelper &getHwHelper() override;
    uint32_t getMaxNumHwThreads() const override;
    xe_result_t registerCLMemory(cl_context context, cl_mem mem, void **ptr) override;
    xe_result_t registerCLProgram(cl_context context, cl_program program,
                                  xe_module_handle_t *phModule) override;
    xe_result_t registerCLCommandQueue(cl_context context, cl_command_queue command_queue,
                                       xe_command_queue_handle_t *phCommandQueue) override;

    NEO::Device *deviceRT = nullptr;
    bool isSubdevice = false;
    void *execEnvironment = nullptr;
    PtrOwn<BuiltinFunctionsLib> builtins = nullptr;
    PtrOwn<MOCSMapper> mocsMapper = nullptr;
    uint32_t maxNumHwThreads = 0;
};

} // namespace L0
