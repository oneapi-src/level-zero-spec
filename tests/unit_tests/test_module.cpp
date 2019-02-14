#include "graphics_allocation.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "module.h"
#include "runtime/platform/platform.h"

#include "igc.opencl.h" // temporarily to instrument NEO's compiler interface

#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <memory>

// temporarily to instrument NEO's compiler interface
namespace Os {
    extern const char *frontEndDllName;
    extern const char *igcDllName;
}

namespace xe {
namespace ult {

using ::testing::Return;

std::unique_ptr<char[]> readBinaryTestFile(const std::string &name, size_t &outSize) {
    std::ifstream file(name, std::ios_base::binary);
    if (false == file.good()) {
        outSize = 0;
        return nullptr;
    }

    size_t length;
    file.seekg(0, file.end);
    length = static_cast<size_t>(file.tellg());
    file.seekg(0, file.beg);

    auto storage = std::make_unique<char[]>(length);
    file.read(storage.get(), length);

    outSize = length;
    return storage;
}

struct UserRealCompilerGuard {
    UserRealCompilerGuard(){
        prevCompilerFcl = Os::frontEndDllName;
        prevCompilerIgc = Os::igcDllName;

        Os::frontEndDllName = FCL_LIBRARY_NAME;
        Os::igcDllName = IGC_LIBRARY_NAME;
    }

    UserRealCompilerGuard(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard(UserRealCompilerGuard &&) = delete;
    UserRealCompilerGuard &operator=(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard &operator=(UserRealCompilerGuard &&) = delete;

    ~UserRealCompilerGuard(){
        Os::frontEndDllName = prevCompilerFcl;
        Os::igcDllName = prevCompilerIgc;
    }

    const char *prevCompilerFcl = nullptr;
    const char *prevCompilerIgc = nullptr;
};


TEST(ModuleCreate, fullBlownModuleTest) {
    UserRealCompilerGuard realCompilerGuard; // just for now

    auto platform = OCLRT::constructPlatform();
    auto success = platform->initialize();
    ASSERT_TRUE(success);

    auto deviceRT = platform->getDevice(0);
    ASSERT_NE(nullptr, deviceRT);
    auto device = Device::create(deviceRT);

    size_t spvModuleSize = 0;
    auto spvModule = readBinaryTestFile("test_files/spv_modules/cstring_module.spv", spvModuleSize);
    ASSERT_NE(0U, spvModuleSize);
  
    xe_module_desc_t modDesc = {};
    modDesc.version = XE_API_HEADER_VERSION;
    modDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    modDesc.inputSize = static_cast<uint32_t>(spvModuleSize);
    modDesc.pInputModule = spvModule.get();

    auto module = whitebox_cast(Module::create(device, &modDesc, deviceRT));
    ASSERT_NE(nullptr, module);

    xe_function_desc_t funDesc = {};
    funDesc.version = XE_API_HEADER_VERSION;
    funDesc.pFunctionName = "memcpy_bytes";
    auto function = whitebox_cast(Function::create(module, &funDesc));
    ASSERT_NE(nullptr, function);

    auto functionArgs = whitebox_cast(FunctionArgs::create(function));
    ASSERT_NE(nullptr, function);

    auto memoryManager = device->getMemoryManager();
    auto dst = memoryManager->allocateDeviceMemory(4096);
    auto src = memoryManager->allocateDeviceMemory(4096);

    uintptr_t dstAddress = static_cast<uintptr_t>(dst->getGpuAddress());
    functionArgs->setValue(0, sizeof(dstAddress), &dstAddress);

    uintptr_t srcAddress = static_cast<uintptr_t>(src->getGpuAddress());
    functionArgs->setValue(1, sizeof(srcAddress), &srcAddress);

    const void *crossThreadData = functionArgs->getCrossThreadDataHostMem();
    ASSERT_NE(nullptr, crossThreadData);
    ASSERT_NE(0U, functionArgs->getCrossThreadDataSize());
    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t*>(crossThreadData);
    const uintptr_t *ctdSearchEnd = ctdSearchBeg + functionArgs->getCrossThreadDataSize() / sizeof(uintptr_t);
    EXPECT_NE(ctdSearchEnd, std::find(ctdSearchBeg, ctdSearchEnd, srcAddress));
    EXPECT_NE(ctdSearchEnd, std::find(ctdSearchBeg, ctdSearchEnd, dstAddress));

    EXPECT_NE(nullptr, function->getIsaHostMem());
    EXPECT_NE(0U, function->getIsaSize());

    auto capturedAllocsFroResidency = functionArgs->getResidencyContainer();
    EXPECT_NE(capturedAllocsFroResidency.end(), std::find(capturedAllocsFroResidency.begin(), capturedAllocsFroResidency.end(), dst));
    EXPECT_NE(capturedAllocsFroResidency.end(), std::find(capturedAllocsFroResidency.begin(), capturedAllocsFroResidency.end(), src));

    functionArgs->destroy();
    function->destroy();
    module->destroy();
}

} // namespace ult
} // namespace xe
