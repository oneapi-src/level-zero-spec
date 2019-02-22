#pragma once
#include "module.h"
#include "mock_device.h"
#include "mock_module.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <memory>
#include <unordered_map>
#include <utility>

namespace xe {

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
};

struct PrecompiledFunctionMock : Mock<Function> {
    PrecompiledFunctionMock(const std::string &precompiledFunctionMockName, const std::string &deviceName);

    PrecompiledFunctionMock(const PrecompiledFunctionMockData *precompiledFunctionMockData)
                            : precompiledFunctionMockData(precompiledFunctionMockData){
        auto bufferArgOffsetPairsIt = precompiledFunctionMockData->bufferArgIndicesAndOffsets;
        auto bufferArgOffsetPairsEnd = bufferArgOffsetPairsIt + precompiledFunctionMockData->bufferArgIndicesAndOffsetsCount;
        while(bufferArgOffsetPairsIt < bufferArgOffsetPairsEnd){
            bufferArgOffsetMap[bufferArgOffsetPairsIt->first] = bufferArgOffsetPairsIt->second;
            ++bufferArgOffsetPairsIt;
        }
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

    const PrecompiledFunctionMockData *precompiledFunctionMockData = nullptr;
    std::unordered_map<int, int> bufferArgOffsetMap;
};

struct PrecompiledFunctionArgsMock : Mock<FunctionArgs> {
    PrecompiledFunctionArgsMock(PrecompiledFunctionMock *function, const std::vector<xe::GraphicsAllocation *> &allocationsForResidency)
        : function(function), allocationsForResidency(allocationsForResidency) { 
        auto crossThreadBaseBeg = reinterpret_cast<const uint8_t *>(function->precompiledFunctionMockData->crossThreadDataBase);
        crossThreadData.assign(crossThreadBaseBeg, crossThreadBaseBeg + function->precompiledFunctionMockData->crossThreadDataBaseSize);
    }

    xe_result_t setValue(uint32_t argIndex, size_t argSize, const void *pArgValue) override {
        auto it = function->bufferArgOffsetMap.find(argIndex);
        if(it == function->bufferArgOffsetMap.end()){
            // not a buffer arg, just assume what's in crossthread data is good enough
            return XE_RESULT_SUCCESS;
        }
        *reinterpret_cast<uintptr_t *>(&crossThreadData[it->second]) = *reinterpret_cast<const uintptr_t*>(pArgValue);
        return XE_RESULT_SUCCESS;
    }

    const void *getCrossThreadDataHostMem() const override {
        return crossThreadData.data();
    }

    size_t getCrossThreadDataSize() const override {
        return function->precompiledFunctionMockData->crossThreadDataBaseSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return allocationsForResidency;
    }

    PrecompiledFunctionMock *function;
    std::vector<xe::GraphicsAllocation *> allocationsForResidency;
    std::vector<uint8_t> crossThreadData;
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
    using DeviceNameToPrecompiledDataMap = std::unordered_map<std::string, const PrecompiledFunctionMockData*>;
    using FunctionNameToPerDevicePrecompiledDataMap = std::unordered_map<std::string, const PrecompiledFunctionMockData*>;
    std::unordered_map<std::string, FunctionNameToPerDevicePrecompiledDataMap> data;
};

struct RegisterPrecompiledFunctionMocksData {
    RegisterPrecompiledFunctionMocksData(const PrecompiledFunctionMockData *data, const std::string &functionName, const std::string &deviceName){
        PrecompiledFunctionMocksDataRegistry::get().registerDataFor(data, functionName, deviceName);
    }
};

inline PrecompiledFunctionMock::PrecompiledFunctionMock(const std::string &precompiledFunctionMockName, const std::string &deviceName)
    : PrecompiledFunctionMock(PrecompiledFunctionMocksDataRegistry::get().getDataFor(precompiledFunctionMockName, deviceName)){
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
        }
        else {
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
                          std::string deviceName, xe::Function *function, xe::FunctionArgs *functionArgs, const std::vector<std::pair<int, uintptr_t>> &bufferArgsIndices,
                          std::ostream &out) {
    out << "// This is a generated file\n";
    out << "// Check " << sourceOrigin << " for details\n\n";
    out << "#include \"tests/unit_tests/mock_module_precompiled.h\"\n"
            "\n"
            "namespace xe {\n"
            "namespace ult {\n\n";

    std::string globalNameSimdSize = mockName + "_SimdSize_" + deviceName;
    std::string globalNameIsa = mockName + "_ISA_" + deviceName;
    std::string globalNameCrossThreadData = mockName + "_CrossThreadDataBase_" + deviceName;
    std::string globalNamePerThreadData = mockName + "_PerThreadDataBase_" + deviceName;
    std::string globalNameBufferArgIndices = mockName + "_BufferArgIndicesAndOffsets_" + deviceName;
    std::string globalNameGroupSize = mockName + "_GroupSizeInPerThreadData_" + deviceName;
    std::string globalNamePrecompiledFunctionMockData = mockName + "_" + deviceName;

    out << "static const uint32_t " << globalNameSimdSize << " = " << function->getSimdSize() << ";\n\n";
    out << "static const uint32_t " << globalNameIsa << "[] = \n";
    writeAsCppArrayInitializer(function->getIsaHostMem(), function->getIsaSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << globalNameCrossThreadData << "[] = \n";
    writeAsCppArrayInitializer(functionArgs->getCrossThreadDataHostMem(), functionArgs->getCrossThreadDataSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << globalNamePerThreadData << "[] = \n";
    writeAsCppArrayInitializer(function->getPerThreadDataHostMem(), function->getPerThreadDataSize(), out);
    out << "\n\n";

    out << "static const std::pair<int, int> " << globalNameBufferArgIndices << "[] = { ";
    const void *crossThreadData = functionArgs->getCrossThreadDataHostMem();
    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t*>(crossThreadData);
    const uintptr_t *ctdSearchEnd = ctdSearchBeg + functionArgs->getCrossThreadDataSize() / sizeof(uintptr_t);
    for(auto buffArgOffset : bufferArgsIndices){
        auto it = std::find(ctdSearchBeg, ctdSearchEnd, buffArgOffset.second);
        assert(it != ctdSearchEnd);
        assert(ctdSearchEnd == std::find(it + 1, ctdSearchEnd, buffArgOffset.second)); // make sure this is not just random number
        auto byteOffset = ((it - ctdSearchBeg) * sizeof(uintptr_t));
        out << "{0x" << buffArgOffset.first << ", 0x" << byteOffset << "}, " ;
    }
    out << " };\n\n";

    uint32_t groupSizeX, groupSizeY, groupSizeZ;
    function->getGroupSize(groupSizeX, groupSizeY, groupSizeZ);
    out << "static const uint32_t " << globalNameGroupSize << "[] = { ";
    out << "0x" << groupSizeX << ", " << "0x" << groupSizeY << ", " << "0x" << groupSizeZ;
    out << " };\n\n";

    out << "static const PrecompiledFunctionMockData " << globalNamePrecompiledFunctionMockData << " {\n"
        << globalNameSimdSize << ",\n"
        << globalNameIsa << ", sizeof(" << globalNameIsa <<"),\n"
        << globalNameCrossThreadData << ", sizeof(" << globalNameCrossThreadData << "),\n"
        << globalNamePerThreadData << ", sizeof(" << globalNamePerThreadData << "),\n"
        << globalNameGroupSize << ",\n"
        << globalNameBufferArgIndices << ", sizeof(" << globalNameBufferArgIndices << ") / sizeof(" << globalNameBufferArgIndices << "[0])\n"
           "};\n\n";

    out << "RegisterPrecompiledFunctionMocksData Register_" << mockName << "_" << deviceName << "{ & " << globalNamePrecompiledFunctionMockData << ", \"" << mockName << "\", \"" << deviceName << "\" }; \n";

    out << "\n"
           "} // namespace xe\n"
           "} // namespace ult\n";
}

} // namespace ult
} // namespace xe
