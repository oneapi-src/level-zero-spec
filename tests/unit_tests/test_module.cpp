#include "graphics_allocation.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "mock_module.h"
#include "module.h"
#include "specialized_module_mock_for_MemcpyBytes_Gen12HPcore.h"

#include "runtime/device/device.h"
#include "runtime/platform/platform.h"

#include "gtest/gtest.h"

#include <fstream>

namespace xe {
namespace ult {

using ::testing::Return;

TEST(xeModuleCreateFunction, redirectsToModuleObject) {
    Mock<Module> module;
    xe_function_desc_t desc = {};
    xe_function_handle_t function = {};

    EXPECT_CALL(module, createFunction(&desc, &function))
        .Times(1)
        .WillRepeatedly(Return(XE_RESULT_SUCCESS));

    auto result = xe::xeModuleCreateFunction(module.toHandle(),
                                             &desc,
                                             &function);
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

inline std::unique_ptr<char[]> readBinaryTestFile(const std::string &name, size_t &outSize) {
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

TEST(ModuleCreate, onlineCompilationModuleTest) {
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
    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t *>(crossThreadData);
    const uintptr_t *ctdSearchEnd = ctdSearchBeg + functionArgs->getCrossThreadDataSize() / sizeof(uintptr_t);
    EXPECT_NE(ctdSearchEnd, std::find(ctdSearchBeg, ctdSearchEnd, srcAddress));
    EXPECT_NE(ctdSearchEnd, std::find(ctdSearchBeg, ctdSearchEnd, dstAddress));

    EXPECT_NE(nullptr, function->getIsaHostMem());
    EXPECT_NE(0U, function->getIsaSize());
    EXPECT_NE(0U, function->getSimdSize());

    auto capturedAllocsFroResidency = functionArgs->getResidencyContainer();
    EXPECT_NE(capturedAllocsFroResidency.end(), std::find(capturedAllocsFroResidency.begin(), capturedAllocsFroResidency.end(), dst));
    EXPECT_NE(capturedAllocsFroResidency.end(), std::find(capturedAllocsFroResidency.begin(), capturedAllocsFroResidency.end(), src));

    ASSERT_NE(nullptr, functionArgs->getPerThreadDataHostMem());
    uint32_t numChannels = 3;
    EXPECT_EQ(numChannels * function->getSimdSize() * sizeof(uint16_t), functionArgs->getPerThreadDataSize());

    uint32_t groupSizeX, groupSizeY, groupSizeZ;
    functionArgs->getGroupSize(groupSizeX, groupSizeY, groupSizeZ);
    EXPECT_EQ(function->getSimdSize(), groupSizeX);
    EXPECT_EQ(1U, groupSizeY);
    EXPECT_EQ(1U, groupSizeZ);

    bool generateMockData = false;
    if (generateMockData) {
        auto deviceName = deviceRT->getFamilyNameWithType();
        std::string moduleName = std::string("MemcpyBytes");
        std::stringstream mockDataStream;
        std::vector<std::pair<int, uintptr_t>> bufferArgsIndices{std::make_pair(0, dstAddress), std::make_pair(1, srcAddress)};
        writeMockData(__FUNCTION__, moduleName, deviceName, function, functionArgs, bufferArgsIndices, mockDataStream);
        std::string mockData = mockDataStream.str();
        std::string fileName = "specialized_module_mock_for_" + moduleName + "_" + deviceName + ".h";
        std::ofstream(fileName, std::ios::binary).write(mockData.data(), mockData.size());
    }

    functionArgs->destroy();
    function->destroy();
    module->destroy();
}

TEST(ModuleCreate, mockedModuleTestGen12HPcore) { // to do : make this generic (i.e. not tied to GEN)
    SpecializedFunctionMock function(MemcpyBytes_SimdSize_Gen12HPcore,
                                     MemcpyBytes_ISA_Gen12HPcore, sizeof(MemcpyBytes_ISA_Gen12HPcore),
                                     MemcpyBytes_CrossThreadDataBase_Gen12HPcore, sizeof(MemcpyBytes_CrossThreadDataBase_Gen12HPcore),
                                     MemcpyBytes_PerThreadDataBase_Gen12HPcore, sizeof(MemcpyBytes_PerThreadDataBase_Gen12HPcore),
                                     MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[0], MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[1], MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[2],
                                     MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore, sizeof(MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore) / sizeof(MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore[0]));

    EXPECT_EQ(MemcpyBytes_SimdSize_Gen12HPcore, function.getSimdSize());
    EXPECT_EQ(MemcpyBytes_ISA_Gen12HPcore, function.getIsaHostMem());
    EXPECT_EQ(sizeof(MemcpyBytes_ISA_Gen12HPcore), function.getIsaSize());

    GraphicsAllocation mockAlloc1{nullptr, 0};
    GraphicsAllocation mockAlloc2{nullptr, 0};
    SpecializedFunctionArgsMock functionArgs(&function, {&mockAlloc1, &mockAlloc2});
    EXPECT_EQ(sizeof(MemcpyBytes_CrossThreadDataBase_Gen12HPcore), functionArgs.getCrossThreadDataSize());
    EXPECT_EQ(0, memcmp(functionArgs.getCrossThreadDataHostMem(), MemcpyBytes_CrossThreadDataBase_Gen12HPcore, sizeof(MemcpyBytes_CrossThreadDataBase_Gen12HPcore)));

    const auto &residencyFromArgs = functionArgs.getResidencyContainer();
    EXPECT_NE(residencyFromArgs.end(), std::find(residencyFromArgs.begin(), residencyFromArgs.end(), &mockAlloc1));
    EXPECT_NE(residencyFromArgs.end(), std::find(residencyFromArgs.begin(), residencyFromArgs.end(), &mockAlloc2));

    auto *crossThreadData = functionArgs.getCrossThreadDataHostMem();

    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t *>(crossThreadData);
    const uintptr_t *ctdSearchEnd = ctdSearchBeg + functionArgs.getCrossThreadDataSize() / sizeof(uintptr_t);

    uintptr_t clearValue = 0;
    uintptr_t addressToPatch = 2357;
    while (ctdSearchEnd != std::find(ctdSearchBeg, ctdSearchEnd, addressToPatch)) {
        ++addressToPatch; // find unique value
    }
    EXPECT_EQ(ctdSearchEnd, std::find(ctdSearchBeg, ctdSearchEnd, addressToPatch));

    functionArgs.setValue(0, sizeof(uintptr_t), &addressToPatch);
    auto arg0 = std::find(ctdSearchBeg, ctdSearchEnd, addressToPatch);
    EXPECT_NE(ctdSearchEnd, arg0);

    functionArgs.setValue(0, sizeof(uintptr_t), &clearValue);
    EXPECT_EQ(ctdSearchEnd, std::find(ctdSearchBeg, ctdSearchEnd, addressToPatch));

    functionArgs.setValue(1, sizeof(uintptr_t), &addressToPatch);
    auto arg1 = std::find(ctdSearchBeg, ctdSearchEnd, addressToPatch);
    EXPECT_NE(ctdSearchEnd, arg1);
    EXPECT_NE(arg0, arg1);

    uint32_t groupSizeX, groupSizeY, groupSizeZ;
    functionArgs.getGroupSize(groupSizeX, groupSizeY, groupSizeZ);
    EXPECT_EQ(MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[0], groupSizeX);
    EXPECT_EQ(MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[1], groupSizeY);
    EXPECT_EQ(MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[2], groupSizeZ);

    EXPECT_EQ(MemcpyBytes_PerThreadDataBase_Gen12HPcore, functionArgs.getPerThreadDataHostMem());
    EXPECT_EQ(sizeof(MemcpyBytes_PerThreadDataBase_Gen12HPcore), functionArgs.getPerThreadDataSize());
}

} // namespace ult
} // namespace xe
