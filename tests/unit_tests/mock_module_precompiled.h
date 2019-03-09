#pragma once
#include "graphics_allocation.h"
#include "module.h"
#include "mock_device.h"
#include "mock_function.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <memory>
#include <unordered_map>
#include <utility>

namespace L0 {

namespace ult {

struct PrecompiledFunctionMockData {
    const uint32_t simdSize;
    const uint32_t *isa;
    const size_t isaSize;
    const uint32_t *crossThreadDataBase;
    const size_t crossThreadDataBaseSize;
    const uint32_t *perThreadDataBase;
    const size_t perThreadDataBaseSize;
    const uint32_t *groupSizeInPerThreadDataBase;
    const std::pair<int, int> *bufferArgIndicesAndOffsets;
    const size_t bufferArgIndicesAndOffsetsCount;
    const bool hasBarriers;
    const uint32_t slmSize;
};

struct PrecompiledFunctionMock : Mock<Function> {

    PrecompiledFunctionMock(const std::string &precompiledFunctionMockName, const std::string &deviceName, const std::vector<L0::GraphicsAllocation *> &allocationsForResidency);
    ~PrecompiledFunctionMock() override {
        delete mockIsaGraphicsAllocation;
    }

    PrecompiledFunctionMock(const std::string &precompiledFunctionMockName, const std::string &deviceName)
        : PrecompiledFunctionMock(precompiledFunctionMockName, deviceName, {}) {}

    PrecompiledFunctionMock(const PrecompiledFunctionMockData *precompiledFunctionMockData)
        : precompiledFunctionMockData(precompiledFunctionMockData) {
        auto bufferArgOffsetPairsIt = precompiledFunctionMockData->bufferArgIndicesAndOffsets;
        auto bufferArgOffsetPairsEnd = bufferArgOffsetPairsIt + precompiledFunctionMockData->bufferArgIndicesAndOffsetsCount;
        while (bufferArgOffsetPairsIt < bufferArgOffsetPairsEnd) {
            bufferArgOffsetMap[bufferArgOffsetPairsIt->first] = bufferArgOffsetPairsIt->second;
            ++bufferArgOffsetPairsIt;
        }
        mockIsaGraphicsAllocation = new GraphicsAllocation(&mockIsaGraphicsAllocationMemory, sizeof(mockIsaGraphicsAllocationMemory)); // TODO : get a better allocation for mock here
    }

    xe_result_t setAttribute(xe_function_set_attribute_t attr,
                             uint32_t value) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getAttribute(xe_function_get_attribute_t attr,
                             uint32_t *pValue) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    uint32_t getSimdSize() const override {
        return precompiledFunctionMockData->simdSize;
    }

    const void *getIsaHostMem() const override {
        return precompiledFunctionMockData->isa;
    }

    size_t getIsaSize() const override {
        return precompiledFunctionMockData->isaSize;
    }

    GraphicsAllocation *getIsaGraphicsAllocation() const override {
        return mockIsaGraphicsAllocation;
    }

    xe_result_t setArgumentValue(uint32_t argIndex, size_t argSize, const void *pArgValue) override {
        auto it = bufferArgOffsetMap.find(argIndex);
        if (it == bufferArgOffsetMap.end()) {
            // not a buffer arg, just assume what's in crossthread data is good enough
            return XE_RESULT_SUCCESS;
        }
        *reinterpret_cast<uintptr_t *>(&crossThreadData[it->second]) = *reinterpret_cast<const uintptr_t *>(pArgValue);
        return XE_RESULT_SUCCESS;
    }

    void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) const override {
        outGroupSizeX = precompiledFunctionMockData->groupSizeInPerThreadDataBase[0];
        outGroupSizeY = precompiledFunctionMockData->groupSizeInPerThreadDataBase[1];
        outGroupSizeZ = precompiledFunctionMockData->groupSizeInPerThreadDataBase[2];
    }

    uint32_t getThreadsPerThreadGroup() const override {
        uint32_t lwsX, lwsY, lwsZ;
        this->getGroupSize(lwsX, lwsY, lwsZ);
        auto lws = lwsX * lwsY * lwsZ;
        auto simd = getSimdSize();

        return (lws + simd - 1) / simd;
    }

    const void *getPerThreadDataHostMem() const override {
        return precompiledFunctionMockData->perThreadDataBase;
    }

    size_t getPerThreadDataSize() const override {
        return precompiledFunctionMockData->perThreadDataBaseSize;
    }

    uint32_t getThreadExecutionMask() const override {
        return 0xfffffffful;
    }

    const void *getCrossThreadDataHostMem() const override {
        return crossThreadData.data();
    }

    size_t getCrossThreadDataSize() const override {
        return precompiledFunctionMockData->crossThreadDataBaseSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return allocationsForResidency;
    }

    bool getHasBarriers() const override {
        return precompiledFunctionMockData->hasBarriers;
    }

    uint32_t getSlmSize() const override {
        return precompiledFunctionMockData->slmSize;
    }

    const PrecompiledFunctionMockData *precompiledFunctionMockData = nullptr;
    std::unordered_map<int, int> bufferArgOffsetMap;

    std::vector<L0::GraphicsAllocation *> allocationsForResidency;
    std::vector<uint8_t> crossThreadData;

    // Fake an allocation for ISA
    alignas(16) uint32_t mockIsaGraphicsAllocationMemory = -1;
    GraphicsAllocation *mockIsaGraphicsAllocation = nullptr;
};

struct PrecompiledFunctionMocksDataRegistry {
    static PrecompiledFunctionMocksDataRegistry &get() {
        static PrecompiledFunctionMocksDataRegistry registry;
        return registry;
    }

    const PrecompiledFunctionMockData *getDataFor(const std::string &functionName, const std::string &deviceName) {
        auto perDeviceMapIt = data.find(deviceName);
        if (data.end() == perDeviceMapIt) {
            return nullptr;
        }
        auto functionDataIt = perDeviceMapIt->second.find(functionName);
        if (perDeviceMapIt->second.end() == functionDataIt) {
            return nullptr;
        }
        return functionDataIt->second;
    }

    void registerDataFor(const PrecompiledFunctionMockData *mockData, const std::string &functionName, const std::string &deviceName) {
        data[deviceName][functionName] = mockData;
    }

  protected:
    using DeviceNameToPrecompiledDataMap = std::unordered_map<std::string, const PrecompiledFunctionMockData *>;
    using FunctionNameToPerDevicePrecompiledDataMap = std::unordered_map<std::string, const PrecompiledFunctionMockData *>;
    std::unordered_map<std::string, FunctionNameToPerDevicePrecompiledDataMap> data;
};

struct RegisterPrecompiledFunctionMocksData {
    RegisterPrecompiledFunctionMocksData(const PrecompiledFunctionMockData *data, const std::string &functionName, const std::string &deviceName) {
        PrecompiledFunctionMocksDataRegistry::get().registerDataFor(data, functionName, deviceName);
    }
};

inline PrecompiledFunctionMock::PrecompiledFunctionMock(const std::string &precompiledFunctionMockName, const std::string &deviceName, const std::vector<L0::GraphicsAllocation *> &allocationsForResidency)
    : PrecompiledFunctionMock(PrecompiledFunctionMocksDataRegistry::get().getDataFor(precompiledFunctionMockName, deviceName)) {
    this->allocationsForResidency = allocationsForResidency;
    auto crossThreadBaseBeg = reinterpret_cast<const uint8_t *>(precompiledFunctionMockData->crossThreadDataBase);
    crossThreadData.assign(crossThreadBaseBeg, crossThreadBaseBeg + precompiledFunctionMockData->crossThreadDataBaseSize);
}

inline void writeAsCppArrayInitializer(const void *data, size_t dataSize, std::ostream &out) { // function taken from cloc
    assert((dataSize & 3) == 0);

    out << "{"
        << std::endl
        << "    ";

    uint32_t *dataUint = (uint32_t *)data;
    for (size_t i = 0; i < (dataSize + 3) / 4; i++) {
        if (i != 0) {
            out << ", ";
            if (i % 8 == 0) {
                out << std::endl
                    << "    ";
            }
        }
        if (i < dataSize / 4) {
            out << "0x" << std::hex << std::setw(8) << std::setfill('0') << dataUint[i];
        } else {
            uint32_t lastBytes = dataSize & 0x3;
            uint32_t lastUint = 0;
            uint8_t *pLastUint = (uint8_t *)&lastUint;
            for (uint32_t j = 0; j < lastBytes; j++) {
                pLastUint[sizeof(uint32_t) - 1 - j] = dataUint[i * 4 + j];
            }
            out << "0x" << std::hex << std::setw(8) << std::setfill('0') << lastUint;
        }
    }
    out << "\n};" << std::endl;
}

inline void writeMockData(const std::string sourceOrigin, std::string &mockName,
                          std::string deviceName, L0::Function *function, const std::vector<std::pair<int, uintptr_t>> &bufferArgsIndices,
                          std::ostream &out) {
    out << "// This is a generated file\n";
    out << "// Check " << sourceOrigin << " for details\n\n";
    out << "#include \"tests/unit_tests/mock_module_precompiled.h\"\n"
           "\n"
           "namespace L0 {\n"
           "namespace ult {\n\n";

    std::string globalNameSimdSize = mockName + "_SimdSize_" + deviceName;
    std::string globalNameIsa = mockName + "_ISA_" + deviceName;
    std::string globalNameCrossThreadData = mockName + "_CrossThreadDataBase_" + deviceName;
    std::string globalNamePerThreadData = mockName + "_PerThreadDataBase_" + deviceName;
    std::string globalNameBufferArgIndices = mockName + "_BufferArgIndicesAndOffsets_" + deviceName;
    std::string globalNameGroupSize = mockName + "_GroupSizeInPerThreadData_" + deviceName;
    std::string globalNamePrecompiledFunctionMockData = mockName + "_" + deviceName;
    std::string globalNameHasBarriers = mockName + "_HasBarriers_" + deviceName;
    std::string globalNameSlmSize = mockName + "_SlmSize_" + deviceName;

    out << "static const uint32_t " << globalNameSimdSize << " = " << function->getSimdSize() << ";\n\n";

    out << "static const uint32_t " << globalNameIsa << "[] = \n";
    writeAsCppArrayInitializer(function->getIsaHostMem(), function->getIsaSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << globalNameCrossThreadData << "[] = \n";
    writeAsCppArrayInitializer(function->getCrossThreadDataHostMem(), function->getCrossThreadDataSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << globalNamePerThreadData << "[] = \n";
    writeAsCppArrayInitializer(function->getPerThreadDataHostMem(), function->getPerThreadDataSize(), out);
    out << "\n\n";

    out << "static const bool " << globalNameHasBarriers << " = " << function->getHasBarriers() << ";\n\n";
    out << "static const uint32_t " << globalNameSlmSize << " = 0x" << function->getSlmSize() << ";\n\n";

    out << "static const std::pair<int, int> " << globalNameBufferArgIndices << "[] = { ";
    const void *crossThreadData = function->getCrossThreadDataHostMem();
    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t *>(crossThreadData);
    const uintptr_t *ctdSearchEnd = ctdSearchBeg + function->getCrossThreadDataSize() / sizeof(uintptr_t);
    for (auto buffArgOffset : bufferArgsIndices) {
        auto it = std::find(ctdSearchBeg, ctdSearchEnd, buffArgOffset.second);
        assert(it != ctdSearchEnd);
        assert(ctdSearchEnd == std::find(it + 1, ctdSearchEnd, buffArgOffset.second)); // make sure this is not just random number
        auto byteOffset = ((it - ctdSearchBeg) * sizeof(uintptr_t));
        out << "{0x" << buffArgOffset.first << ", 0x" << byteOffset << "}, ";
    }
    out << " };\n\n";

    uint32_t groupSizeX, groupSizeY, groupSizeZ;
    function->getGroupSize(groupSizeX, groupSizeY, groupSizeZ);
    out << "static const uint32_t " << globalNameGroupSize << "[] = { ";
    out << "0x" << groupSizeX << ", "
        << "0x" << groupSizeY << ", "
        << "0x" << groupSizeZ;
    out << " };\n\n";

    out << "static const PrecompiledFunctionMockData " << globalNamePrecompiledFunctionMockData << " {\n"
        << globalNameSimdSize << ",\n"
        << globalNameIsa << ", sizeof(" << globalNameIsa << "),\n"
        << globalNameCrossThreadData << ", sizeof(" << globalNameCrossThreadData << "),\n"
        << globalNamePerThreadData << ", sizeof(" << globalNamePerThreadData << "),\n"
        << globalNameGroupSize << ",\n"
        << globalNameBufferArgIndices << ", sizeof(" << globalNameBufferArgIndices << ") / sizeof(" << globalNameBufferArgIndices << "[0]),\n"
        << globalNameHasBarriers << ",\n"
        << globalNameSlmSize << "\n"
                                "};\n\n";

    out << "RegisterPrecompiledFunctionMocksData Register_" << mockName << "_" << deviceName << "{ & " << globalNamePrecompiledFunctionMockData << ", \"" << mockName << "\", \"" << deviceName << "\" }; \n";

    out << "\n"
           "} // namespace L0\n"
           "} // namespace ult\n";
}

} // namespace ult
} // namespace L0
